#include "sockstream/sockstream.hpp"
#include <unistd.h>

namespace cc
{

/*
 *
 * CTOR, DTOR
 *
 */

sockstream::sockstream()
    : __mode{UNSET}, __domain{AF_INET}, __fd{-1}, __client_fd{-1}, __buff{new char[MAX_MSG_SIZE]}, __buff_sz{0}
{
    __fd = socket(AF_INET, SOCK_STREAM, 0);
    if (__fd < 0)
        throw sockstream_exception(sockstream_exception::CREATE_FD);
}

sockstream::sockstream(transport_protocol t_proto, network_protocol n_proto)
    : __mode{UNSET}, __domain{n_proto},__fd{-1}, __client_fd{-1}, __buff{new char[MAX_MSG_SIZE]}, __buff_sz{0}
{
    int __n_proto;
    switch (n_proto)
    {
    case IPv4:
        __n_proto = AF_INET; 
        break;
    case IPv6: 
        __n_proto = AF_INET6;
        break;
    default:
        throw std::invalid_argument("Invalid network protocol specified. Must be 'IPv4' or 'IPv6'.");
    }

    int __t_proto;
    switch (t_proto)
    {
    case TCP:
        __t_proto = SOCK_STREAM; break;
    case UDP:
        __t_proto = SOCK_DGRAM; break;
    default: 
        throw std::invalid_argument("Invalid transport protocol specified. Must be 'TCP' or 'UDP'.");
    }
    __domain = __n_proto;
    __fd = socket(__n_proto, __t_proto, 0);
    if (__fd < 0)
        throw sockstream_exception(sockstream_exception::CREATE_FD);
}

sockstream::sockstream(int domain, int type, int protocol = 0)
    : __mode{UNSET}, __domain{domain}, __fd{-1}, __client_fd{-1}, __buff{new char[MAX_MSG_SIZE]}, __buff_sz{0}
{
    __fd = socket(domain, type, protocol);
    if (__fd < 0)
        throw sockstream_exception(sockstream_exception::CREATE_FD);
}

sockstream::~sockstream()
{
    close(__fd);
    delete[] __buff;
}

} // NAMESPACE CC
