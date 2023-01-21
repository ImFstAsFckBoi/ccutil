#include "sockstream/exception.hpp"

namespace cc
{

/*
 * SOCKET EXCEPTION
 *
 */

sockstream_exception::sockstream_exception(sockstream_exception::sockstream_except_t type)
    : std::exception{}, __type{type}, __msg{}
{
    switch (__type)
    {
    case CREATE_FD:
        __msg = "Failed to create a POSIX socket file descriptor.";
        break;
    case UNSET:
        __msg = "Socket mode is uninitiated. call connect() or bind() to initiate the socket to client or server mode.";
        break;
    case SET:
        __msg = "Socket mode has  already been set.";
        break;
    case ADDR_CON:
        __msg = "Failed to convert string address to binary. Address is probably formatted incorrectly";
        break;
    case CONNECT:
        __msg = "Failed to connect to server endpoint.";
        break;
    case OPT:
        __msg = "Failed to set socket options.";
        break;
    case BIND:
        __msg = "Failed to bind to address. Most often this is because this port is already occupied.";
        break;
    case LISTEN:
        __msg = "Failed to start listen on server socket.";
        break;
    case ACCEPT:
        __msg = "Failed to accept an incoming client connection.";
        break;
    case BUFF:
        __msg = "Stream buffer in full and needs to be flushed.";
        break;
    case READ:
        __msg = "Failed to read from the socket.";
        break;
    case WRITE:
        __msg = "Failed to write to the socket";
        break;
    default:
        __msg = "Unkown error.";
        break;
    }
}

const char *sockstream_exception::what() const throw()
{
    return __msg.c_str();
}

} // NAMESPACE CC
