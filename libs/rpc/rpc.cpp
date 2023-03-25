#include "rpc.hpp"
#include <spdlog/spdlog.h>
#include <functional>
#include <iostream>
#include <boost/lexical_cast.hpp>

#define MEM_FN1(x,y) std::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z) boost::bind(&self_type::x, shared_from_this(),y,z)

namespace fb
{
    rpc::rpc(boost::asio::io_context& io_context, const std::string& server, const std::string& path)
    : 
    _resolver(io_context),
    _socket(io_context)
    {
        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        std::ostream request_stream(&_request);
        request_stream << "GET " << path << " HTTP/1.0\r\n";
        request_stream << "Host: " << server << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Start an asynchronous resolve to translate the server and service names
        // into a list of endpoints.
        _resolver.async_resolve(server, "http",
            boost::bind(&rpc::handle_resolve, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::results));
    }

    void rpc::start(ip::tcp::endpoint ep)
    {
        
    }

    void rpc::handle_resolve(const boost::system::error_code& err, const tcp::resolver::results_type& endpoints)
    {
        if (!err)
        {
            // Attempt a connection to each endpoint in the list until we
            // successfully establish a connection.
            boost::asio::async_connect(_socket, endpoints,
                boost::bind(&rpc::handle_connect, this,
                boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void rpc::handle_connect(const boost::system::error_code& err)
    {
        if (!err)
        {
            // The connection was successful. Send the request.
            boost::asio::async_write(_socket, _request,
                boost::bind(&rpc::handle_write_request, this,
                boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void rpc::handle_write_request(const boost::system::error_code& err)
    {
        if (!err)
        {
        // Read the response status line. The _response streambuf will
        // automatically grow to accommodate the entire line. The growth may be
        // limited by passing a maximum size to the streambuf constructor.
            boost::asio::async_read_until(_socket, _response, "\r\n",
                boost::bind(&rpc::handle_read_status_line, this,
                boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void rpc::handle_read_status_line(const boost::system::error_code& err)
    {
        if (err)
            std::cout << "Error: " << err << "\n";
         
        // Check that response is OK.
        std::istream response_stream(&_response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cout << "Invalid response\n";
            return;
        }
        if (status_code != 200)
        {
            std::cout << "Response returned with status code ";
            std::cout << status_code << "\n";
            return;
        }

        // Read the response headers, which are terminated by a blank line.
        boost::asio::async_read_until(_socket, _response, "\r\n\r\n",
            boost::bind(&rpc::handle_read_headers, this,
            boost::asio::placeholders::error));
    }

    void rpc::handle_read_headers(const boost::system::error_code& err)
    {
        if (err)
            std::cout << "Error: " << err << "\n";

        // Process the response headers.
        std::istream response_stream(&_response);
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            std::cout << header << "\n";
        std::cout << "\n";

        // Write whatever content we already have to output.
        if (_response.size() > 0)
            std::cout << &_response;

        // Start reading remaining data until EOF.
        boost::asio::async_read(_socket, _response,
            boost::asio::transfer_at_least(1),
            boost::bind(&rpc::handle_read_content, this,
            boost::asio::placeholders::error));
    }

    void rpc::handle_read_content(const boost::system::error_code& err)
    {
        if (err)
            std::cout << "Error: " << err << "\n";

        // Write all of the data that has been read so far.
        std::cout << &_response;

        // Continue reading remaining data until EOF.
        boost::asio::async_read(_socket, _response,
            boost::asio::transfer_at_least(1),
            boost::bind(&rpc::handle_read_content, this,
            boost::asio::placeholders::error));
    }

}