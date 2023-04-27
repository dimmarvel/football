
#include <server/hub.hpp>
#include <spdlog/spdlog.h>
#include <server/server.hpp>

namespace fb
{
    hub::hub(api::api_application& app)
    :
    _app(app),
    _server(std::make_shared<tcp_server>(_app)),
    _timer(_app.get_context()) //6000 to constant

// TIMER FIX

    {}

    void hub::start()
    {
        subscribe_on_server();
        _server->start();
        _timer.start([this]() -> bool
        {
            show_connections();
            return false;
        });
    }

    void hub::subscribe_on_server()
    {
        add_event(_server, _server->accept_connection_ev.connect(std::bind(&hub::on_new_connect, shared_from_this(), core::pl::_1)));
    }

    void hub::subscribe_on_connection(api::connect_ptr c)
    {
        add_event(c, c->close_connection_ev.connect(std::bind(&hub::on_close_connect, shared_from_this(), core::pl::_1)));
        add_event(c, c->message_ev.connect(std::bind(&hub::on_message, shared_from_this(), core::pl::_1, core::pl::_2)));
    }

    void hub::on_new_connect(api::connect_ptr c)
    {
        spdlog::info("[hub] add new connection {}:{}", c->socket().remote_endpoint().address().to_string(), c->socket().remote_endpoint().port());
        subscribe_on_connection(c);
        _connections.insert(c);
        c->start();
    }

    void hub::on_close_connect(api::connect_ptr c)
    {
        spdlog::info("[hub] close connection {}", c->socket().remote_endpoint().address().to_string());
        remove_events(c);
        _connections.erase(c);
    }

    void hub::on_message(api::connect_ptr c, std::string msg)
    {
        spdlog::info("[hub] from {} message: {}", c->socket().remote_endpoint().address().to_string(), msg);
        c->send("ping\n");
    }

    void hub::show_connections()
    {
        spdlog::info("----------Connections({})----------", _connections.size());
        size_t i = 0;
        for(const auto it : _connections)
            spdlog::info("{}) address - {}", i++, it->socket().remote_endpoint().address().to_string());
        spdlog::info("----------------------------------");
    }

}