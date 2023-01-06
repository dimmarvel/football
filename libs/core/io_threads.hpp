#pragma once

#include <thread>
#include <vector>

namespace boost::asio {
    class io_context;
}

namespace fb::core {
    
    constexpr const uint32_t MINIMUM_REQUIRED_THREADS = 4;
    
    class io_threads
    {
    public:
        explicit io_threads(boost::asio::io_context& ctx);
        ~io_threads();

        std::size_t start(std::size_t n = std::max(MINIMUM_REQUIRED_THREADS, std::thread::hardware_concurrency()));
        void join();

    private:
        boost::asio::io_context& _ctx;
        std::vector<std::thread> _threads;

        void run();
    };
}
