#pragma once
#include <api_types.hpp>

#include <boost/asio/deadline_timer.hpp>
#include <ctime>

namespace boost::asio
{
    class any_io_executor;
}

namespace fb::core {

    api::timestamp_t now();

    class timer
    {
    public:
        timer(boost::asio::any_io_executor ctx, api::timestamp_t interval, bool async = true);
        ~timer();

        void start(std::function<bool()> callback);
        void start(api::timestamp_t ends_at, std::function<bool()> callback);
        void stop();

        api::timestamp_t interval() const { return _interval; }
        bool async() const { return _async; }

    private:
        bool                        _async;
        std::atomic_bool            _active = false;
        api::timestamp_t            _interval;
        boost::asio::deadline_timer _timer;
    };
}
