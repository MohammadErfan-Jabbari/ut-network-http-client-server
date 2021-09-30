//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

enum { max_length = 1024 };

const std::string HOST = "127.0.0.1"; 
const std::string PORT = "4433"; 

int main()
{
    try
    {
        boost::asio::io_context io_context;

        tcp::socket mySocket(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(mySocket, resolver.resolve(HOST, PORT));

        string request = "Thiss is a simple message from client to server.\n";
        
        cout << "this is the message" << endl;

        boost::asio::write(mySocket, boost::asio::buffer(request, 1024));

        std::string reply;

        boost::asio::read(mySocket, boost::asio::buffer(reply, 1024));

        cout << "This is reply" << reply << endl;
        
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

     return 0;
}