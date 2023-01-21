#include "sockstream/sockstream.hpp"

#include <cstring>
#include <exception>

namespace cc
{

/*
 *
 * CONNECTIONS
 *
 */

/**
 * @brief convert localhost to ip address
 * 
 * @param str "localhost"
 * @param domain "AF_INET, AF_INET6, etc"
 * @return std::string 
 */
std::string __lh2ip(std::string const &str, int domain)
{
    switch (domain)
    {
    case AF_INET:
        return (str == "localhost" ? "127.0.0.1" : str);
    case AF_INET6:
        return (str == "localhost" ? "::1" : str);
    default:
        throw std::logic_error("Network protocol not implemented");
    }
}

void sockstream::connect(std::string const &str_addr, int port)
{
    sockaddr_in addr;
    std::string _str_addr = __lh2ip(str_addr, __domain);

    if (__mode != UNSET)
        throw sockstream_exception(sockstream_exception::SET);

    __mode = CLIENT;

    bzero(&addr, sizeof(addr));

    addr.sin_family = __domain;
    addr.sin_port = htons(port);
    // inet_pton() return 1 for success and 0 for failure (WHAT)
    if (!inet_pton(__domain, _str_addr.c_str(), &addr.sin_addr))
        throw sockstream_exception(sockstream_exception::ADDR_CON);

    if (::connect(__fd, (sockaddr *)&addr, sizeof(addr)))
        throw sockstream_exception(sockstream_exception::CONNECT);
}

void sockstream::bind(std::string const &str_addr, int port)
{

    sockaddr_in addr;

    std::string _str_addr = __lh2ip(str_addr, __domain);

    if (__mode != UNSET)
        throw sockstream_exception(sockstream_exception::SET);

    __mode = SERVER;

    int opt = 1;
    if (setsockopt(__fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        throw sockstream_exception(sockstream_exception::OPT);

    bzero(&addr, sizeof(addr));

    addr.sin_family = __domain;

    if (!inet_pton(__domain, _str_addr.c_str(), &addr.sin_addr))
        throw sockstream_exception(sockstream_exception::ADDR_CON);

    addr.sin_port = htons(port);

    if (::bind(__fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        throw sockstream_exception(sockstream_exception::BIND);

    if (listen(__fd, 3) < 0)
        throw sockstream_exception(sockstream_exception::LISTEN);

    if ((__client_fd = accept(__fd, NULL, NULL)) < 0)
        throw sockstream_exception(sockstream_exception::ACCEPT);
}

void sockstream::bind(int port)
{
    bind("0.0.0.0", port);
}


} // NAMESPACE CC
