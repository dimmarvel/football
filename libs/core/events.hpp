#pragma once
#include <boost/signals2.hpp>
#include <mutex>
#include <unordered_map>

namespace boost::asio
{
    class any_io_executor;
}

namespace fb::core {

    namespace bs2 = boost::signals2;
    namespace pl = std::placeholders;
   
    using bs2_con = bs2::connection;

    class publisher_base {}; 

    class subscriber
    {
        
    public:
        ~subscriber()
        {
            unsubscribe();
        }

        void add_event(const std::shared_ptr<publisher_base>& p, const bs2_con& event)
        {
            std::lock_guard _(_m);
            _events.emplace(p, event);
        }
        
        void remove_events(const std::shared_ptr<publisher_base> p)
        {
            std::lock_guard _(_m);
            _events.erase(p);
        }

        void unsubscribe()
        {
            std::lock_guard _(_m);
            auto it = _events.begin();
            while(it != _events.end())
            {
                it->second.disconnect();
                it = _events.erase(it);
            }
        }

    private:
        mutable std::mutex _m;
        std::unordered_map<std::shared_ptr<publisher_base>, bs2_con> _events;
    };

}
