#include "rpc.hpp"
#include <spdlog/spdlog.h>
#include <functional>
#include <iostream>
#include <boost/lexical_cast.hpp>

#define MEM_FN1(x,y) std::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z) boost::bind(&self_type::x, shared_from_this(),y,z)

namespace fb
{
    namespace pl = std::placeholders;

    rpc::rpc(fb::client::application& app) 
    : 
    _app(app),
    _sock(_app.get_context()),
    _started(true), 
    _username("usr"), 
    _timer(_app.get_context()) 
    {}

    void rpc::start(ip::tcp::endpoint ep) 
    {
        spdlog::info("[rpc] rpc start at: {}", ep.address().to_string());
        _sock.async_connect(ep, std::bind(&rpc::on_connect, shared_from_this(), pl::_1));
    }

    void rpc::stop() 
    {
        if (!_started) return;
        _started = false;
        _sock.close();
        spdlog::warn("[rpc] stop");
    }
    
    void rpc::on_connect(const error_code & err) 
    {
        if (!err)
        {
            do_read();
            send_msg("ping");
        }
        else 
            stop();
    }

    void rpc::on_read(const error_code& err, size_t bytes) 
    {
        if (err) 
            stop();
        
        if (!started()) 
        {
            spdlog::warn("[rpc] rpc doesn't start");
            return;
        }
            
        // process the msg
        std::string msg(_read_buffer, bytes);
        spdlog::info("[rpc] get message: {}", msg);
        if (msg.find("ping") == 0) do_ping();
        else spdlog::warn("[prc] ERROR coming not ping it is: {}", msg);
        do_read();
    }

    void rpc::do_ping() 
    {
        spdlog::info("[rpc] send ping message"); 
        send_msg("ping"); 
    }
    
    void rpc::on_write(const error_code& err, size_t bytes) 
    { 
        spdlog::info("write call some logic");
    }
    
    void rpc::do_read() 
    {
        spdlog::info("[rpc] start read");
        async_read(_sock, buffer(_read_buffer), boost::asio::transfer_all(), 
                                                MEM_FN2(on_read, pl::_1, pl::_2));
    }
    
    void rpc::send_msg(const std::string& msg) 
    {
        if (!started()) return;

        _send_size = boost::lexical_cast<std::string>(msg.size());
        spdlog::info("[rpc] send message size = {}", _send_size);
        _sock.async_write_some(buffer(_send_size, _send_size.size()), 
            [self = shared_from_this(), msg](const error_code& err, size_t bytes)
            {
                if(err)
                {
                    spdlog::error("[rpc] error"); 
                    return;
                }
                self->send_msg_data(msg);
            });
    }

    void rpc::send_msg_data(const std::string& msg) 
    {
        if (!started()) return;

        spdlog::info("[rpc] send message = {}", msg);
        _sock.async_write_some(buffer(msg.data(), msg.size()), MEM_FN2(on_write, pl::_1, pl::_2));
    }

}