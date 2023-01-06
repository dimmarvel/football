#include "rpc.hpp"
#include <spdlog/spdlog.h>

#define MEM_FN1(x,y) std::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z) boost::bind(&self_type::x, shared_from_this(),y,z)

namespace fb
{
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
        _sock.async_connect(ep, std::bind(&rpc::on_connect, shared_from_this(), std::placeholders::_1));
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
            do_ping();
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
        if (msg.find("ping") == 0) on_ping(msg);
    }


    void rpc::on_ping(const std::string& msg) 
    {
        std::istringstream in(msg);
        std::string answer;
        in >> answer >> answer;
        spdlog::info("[rpc] get ping message");
        postpone_ping();
    }


    void rpc::do_ping() 
    {
        spdlog::info("[rpc] send ping message"); 
        do_write("ping\n"); 
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
        async_read(_sock, buffer(_read_buffer), MEM_FN2(read_complete,_1,_2), MEM_FN2(on_read,_1,_2));
    }
    
    void rpc::do_write(const std::string& msg) 
    {
        if ( !started() ) return;
        std::copy(msg.begin(), msg.end(), _write_buffer);
        _sock.async_write_some(buffer(_write_buffer, msg.size()), MEM_FN2(on_write,_1,_2));
    }

    size_t rpc::read_complete(const boost::system::error_code& err, size_t bytes) 
    {
        if(err) 
            return 0;

        bool found = std::find(_read_buffer, _read_buffer + bytes, '\n') < _read_buffer + bytes;
        
        return found ? 0 : 1;
    }

}