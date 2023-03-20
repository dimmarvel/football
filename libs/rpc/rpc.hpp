#pragma once

#define BOOST_BIND_NO_PLACEHOLDERS

#include <client/application.hpp>
#include <boost/bind.hpp>
#include <spdlog/spdlog.h>

namespace fb::client
{
    class application;
}

namespace fb
{
    using namespace boost::asio; // TODO: delete?

    class rpc : public std::enable_shared_from_this<rpc>
    {
        typedef rpc self_type;
    public:
        typedef boost::system::error_code error_code;
        typedef boost::shared_ptr<rpc> self_ptr;
        
        rpc(fb::client::application& app);

        void start(ip::tcp::endpoint ep);

        void stop();
        bool started() { return _started; }
        
        void on_connect(const error_code& err);

        void on_read(const error_code& err, size_t bytes);
        void on_write(const error_code& err, size_t bytes);
        void do_read();
        void send_msg(const std::string& msg);

        void do_ping();

    private:
        void send_msg_data(const std::string& msg); 

    private:
        fb::client::application& _app;
        ip::tcp::socket _sock;
        enum { max_msg = 1024 };
        char _read_buffer[max_msg];
        std::string _send_size;
        std::string _send_msg;
        bool _started;
        std::string _username;
        deadline_timer _timer;
    };

}