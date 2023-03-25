#pragma once
#include <api_connection.hpp>

#include <boost/asio.hpp>

namespace fb
{
    using namespace boost::asio; // TODO: delete?

    class connection :  public api::api_connection,
                        public std::enable_shared_from_this<connection>,
                        public api::connection_events
    {
    public:

        static api::connect_ptr create(api::api_application& app) // TODO: refactor
        {
            return api::connect_ptr{new connection(app)};
        }

        void start();

        virtual ip::tcp::socket& socket() override;
        virtual void send(std::string message) override;

        void handle_write(const boost::system::error_code& err, size_t s);
        void handle_receive(const boost::system::error_code & err, size_t read_bytes);
        void on_read();
        void on_msg_ready();
        void async_read();

    private:
        connection(api::api_application& app);

        using strand_t = boost::asio::strand<boost::asio::any_io_executor>;
    private:
        api::api_application& _app;
        ip::tcp::socket _socket;
        strand_t        _rstrand;
        std::string     _rbuffer;
        size_t          _rsize = 0;
    };
}