#pragma once
#include <api_application.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <core/events.hpp>
#include <unordered_set>

namespace fb
{
    class connection;
}

namespace fb::api
{
    using connect_ptr = std::shared_ptr<connection>;
    using socket_t = boost::asio::ip::tcp::socket;
    using connections = std::unordered_set<std::shared_ptr<connection>>;

    class connection_events : public core::publisher_base
    {
        using close_connection_ev_t = core::bs2::signal<void(api::connect_ptr)>;
        using message_ev_t = core::bs2::signal<void(api::connect_ptr, std::string)>;
    public:
        close_connection_ev_t close_connection_ev;
        message_ev_t message_ev;
    };

    class api_connection
    {
    public:
        virtual socket_t& socket() = 0;
        virtual void send(std::string message) = 0;
    };
}