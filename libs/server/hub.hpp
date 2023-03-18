#pragma once
#include <api_hub.hpp>
#include <core/events.hpp>
#include <server/connection.hpp>
#include <core/timer.hpp>


namespace fb
{
    class tcp_server;
}

namespace fb
{
    class hub : public api::api_hub,
                public std::enable_shared_from_this<hub>,
                public core::subscriber
    {
    public:
        hub(api::api_application& app);

    public:
        void start() override;
        void subscribe_on_server() override;
        void subscribe_on_connection(api::connect_ptr c);
        
        void on_new_connect(api::connect_ptr c) override;
        void on_close_connect(api::connect_ptr c);
        void on_message(api::connect_ptr c, std::string msg);

    private:
        void show_connections();

    private:
        api::api_application&           _app;
        std::shared_ptr<tcp_server>     _server;

        api::connections _connections;

        core::timer _timer;
        std::mutex  _mutex;
    };
}