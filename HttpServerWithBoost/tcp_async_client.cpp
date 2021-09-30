#include <boost/asio.hpp>
#include <thread>
#include <mutex>
#include <memory>
#include <iostream>

using namespace boost;

// Function pointer type that points to the callback
// function which is called when a request is complete.
typedef void(*Callback) (unsigned int request_id,
const std::string& response,
const system::error_code& ec);

// Structure represents a context of a single request.
struct Session {
Session(asio::io_service& ios,
const std::string& raw_ip_address,
unsigned short port_num,
const std::string& request,
unsigned int id,
Callback callback) :
m_sock(ios),
m_ep(asio::ip::address::from_string(raw_ip_address),
port_num),
m_request(request),
m_id(id),
m_callback(callback),
m_was_cancelled(false) {}
asio::ip::tcp::socket m_sock; // Socket used for communication
asio::ip::tcp::endpoint m_ep; // Remote endpoint.
std::string m_request; // Request string.
// streambuf where the response will be stored.
asio::streambuf m_response_buf;
std::string m_response; // Response represented as a string.
// Contains the description of an error if one occurs during
// the request life cycle.
system::error_code m_ec;
unsigned int m_id; // Unique ID assigned to the request.
// Pointer to the function to be called when the request
// completes.
Callback m_callback;
bool m_was_cancelled;
std::mutex m_cancel_guard;
};
