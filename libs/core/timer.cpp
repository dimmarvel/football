#include "timer.hpp"
#include <chrono>
#include <boost/asio.hpp>

namespace fb::core {
    
    api::timestamp_t now()
    {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto since = now.time_since_epoch();
        return duration_cast<nanoseconds>(since).count();
    }

    timer::timer(boost::asio::any_io_executor ctx, api::timestamp_t interval, bool async)
    :   
    _async(async),
    _active(false),
    _interval(interval),
    _timer(ctx)
    {}

    timer::~timer()
    {
        stop();
    }

    void timer::start(std::function<bool()> callback)
    {
        _active = true;
        _timer.expires_from_now(boost::posix_time::millisec(_interval));
        if (_async)
        {
            _timer.async_wait([this, callback](const boost::system::error_code& ec)
            {
                if(ec == boost::asio::error::operation_aborted)
                    return;
                
                if(!callback())
                    start(callback);
                else
                    _active = false;
            });
        }
        else
        {
            _timer.wait();
            if(!callback())
                start(callback);
            else
                _active = false;
        }
    }

    void timer::start(api::timestamp_t ends_at, std::function<bool()> callback)
    {
        auto expr = [ends_at, callback]() -> bool
        {
            if(now() >= ends_at)
                return true;
            return callback();
        };
        start(expr);
    }

    void timer::stop()
    {
        _active = false;
        _timer.cancel();
    }   
}
