#pragma once
#include <api_types.hpp>
#include <api_application.hpp>
#include <api_connection.hpp>
#include <core/events.hpp>

namespace fb
{
    class connection;
}

namespace fb::api
{

    class server_events : public core::publisher_base
    {
        using accept_connection_ev_t = core::bs2::signal<void(api::connect_ptr)>;
    public:
        accept_connection_ev_t accept_connection_ev;
    };

    class api_server
    {
    public:
        virtual ~api_server() {}

        virtual void start() = 0;

        virtual void start_accept() = 0;
        virtual void handle_accept(api::socket_t&& sock, const boost::system::error_code& error) = 0;
    };
}