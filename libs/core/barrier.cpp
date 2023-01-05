#include "barrier.hpp"

namespace fb::core {

    barrier::barrier(std::size_t count)
        :   _count(count)
    {}

    void barrier::wait()
    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (--_count == 0)
        {
            _cv.notify_all();
        }
        else
        {
            _cv.wait(lock, [this] { return _count == 0; });
        }
    }
}
