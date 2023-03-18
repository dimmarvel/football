#include "rpc.hpp"
#include <spdlog/spdlog.h>
#include <functional>

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
    }
    
    void rpc::on_connect(const error_code & err) 
    {
        if (!err) 
            postpone_ping();
        else 
            stop();
    }

    void rpc::on_read(const error_code& err, size_t bytes) 
    {
        if (err) 
            stop();
        
        if (!started()) 
            return;
            
        // process the msg
        std::string msg(_read_buffer, bytes);
        spdlog::info("[rpc] get message: {}", msg);
        if (msg.find("ping") == 0) on_ping(msg);
    }

    void rpc::on_ping(const std::string& msg) 
    {
        postpone_ping();
    }

    void rpc::do_ping() 
    {
        spdlog::info("[rpc] send ping message"); 
        send_msg("ping"); 
    }

    void rpc::postpone_ping() 
    {
        _timer.expires_from_now(boost::posix_time::millisec(rand() % 7000));
        _timer.async_wait(std::bind(&rpc::do_ping, shared_from_this()));
    }
    
    void rpc::on_write(const error_code& err, size_t bytes) 
    { 
        do_read(); 
    }
    
    void rpc::do_read() 
    {
        async_read(_sock, buffer(_read_buffer), MEM_FN2(read_complete, pl::_1, pl::_2), 
                                                MEM_FN2(on_read, pl::_1, pl::_2));
    }
    
    void rpc::send_msg(const std::string& msg) 
    {
        if (!started()) return;

        uint32_t size = msg.size(); // send size
        _sock.async_write_some(buffer(&size, sizeof(decltype(size))), 
            [self = shared_from_this(), &size, &msg](const error_code& err, size_t bytes)
            {
                if(err)
                {
                    spdlog::error("[rpc] error"); 
                    return;
                }
                self->send_msg_data(msg, size);
            });
    }

    void rpc::send_msg_data(const std::string& msg, uint32_t size) 
    {
        if (!started()) return;

        _sock.async_write_some(buffer(msg.data(), size), MEM_FN2(on_write, pl::_1, pl::_2));
    }

    size_t rpc::read_complete(const boost::system::error_code& err, size_t bytes) 
    {
        if(err) 
            return 0;

        bool found = std::find(_read_buffer, _read_buffer + bytes, '\n') < _read_buffer + bytes;
        
        return found ? 0 : 1;
    }

}