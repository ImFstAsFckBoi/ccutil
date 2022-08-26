#include "sockstream.hpp"

#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <cstdlib>

namespace cc {


/*
 * 
 * CTOR, DTOR, ASSIGN 
 * 
 */

sockstream::sockstream()
    : __mode{UNSET}, __fd{-1}, __client_fd{-1}, __buff{new char[MAX_MSG_SIZE]}, __buff_sz{0}
{
    __fd = socket(AF_INET, SOCK_STREAM, 0);
    if (__fd < 0)
        throw std::runtime_error("Failed to create socket file descriptor.");
}


sockstream::~sockstream()
{
    close(__fd);
    delete[] __buff;
}
/*
 * 
 * CONNECTIONS
 * 
 */


void sockstream::connect(std::string const &str_addr, int port)
{
    sockaddr_in addr;
    std::string _str_addr = (str_addr == "localhost" ? "127.0.0.1" : str_addr);
    
    if (__mode != UNSET)
        throw std::logic_error("This object has already been connected or bound.");

    __mode = CLIENT;

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // inet_pton() return 1 for success and 0 for failure (WHAT)
    if (!inet_pton(AF_INET, _str_addr.c_str(), &addr.sin_addr))
        throw std::runtime_error("Failed to convert address string to binary.");

    if (::connect(__fd, (sockaddr *) &addr, sizeof(addr)))
        throw std::runtime_error("Failed to connect socket.");

}


void sockstream::bind(std::string const &str_addr, int port)
{

    sockaddr_in addr;

    std::string _str_addr = (str_addr == "localhost" ? "127.0.0.1" : str_addr);

    if (__mode != UNSET)
        throw std::logic_error("This object has already been connected or bound.");

    __mode = SERVER;

    int opt = 1;
    if (setsockopt(__fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        throw std::runtime_error("Failed to set socket options.");

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    
    if (!inet_pton(AF_INET, _str_addr.c_str(), &addr.sin_addr))
        throw std::runtime_error("Failed to convert address string to binary.");

    addr.sin_port = htons(port);

    if (::bind(__fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Failed to bind the socket");

    if (listen(__fd, 3) < 0)
        throw std::runtime_error("Failed to start listening.");

    if ((__client_fd = accept(__fd, NULL, NULL)) < 0)
        throw std::runtime_error("Failed to accept a new connecting client.");

}


void sockstream::bind(int port)
{
    bind("0.0.0.0", port);
}


/*
 * 
 * BUFFER MANIPULATORS
 * 
 */


void sockstream::put(char c)
{
    if (1 + __buff_sz > MAX_MSG_SIZE)
    {
        // throw
    }

    __buff[__buff_sz++] = c;
}


void sockstream::put(std::string const &str)
{
    if (str.size() + __buff_sz > MAX_MSG_SIZE)
    {
        // throw
    }

    memcpy(__buff + __buff_sz, str.data(), str.size());
    __buff_sz += str.size();
}


ssize_t sockstream::read(char *buff, size_t buff_len)
{
    ssize_t i;
    int fd;

    switch (__mode)
    {
    case SERVER:
        fd = __client_fd;
        break;
    case CLIENT:
        fd = __fd;
        break;
    case UNSET:
        // TODO: throw some sjit
        break;
    }

    i = ::read(fd, buff, buff_len);
    if (i == -1)
        throw std::runtime_error("Failed to read incoming message.");

    return i;
}

void sockstream::read(std::string &str_buff)
{
    char buff[MAX_MSG_SIZE]{};
    read(buff, MAX_MSG_SIZE);
    str_buff = buff;
}


std::string sockstream::read()
{
    char buff[MAX_MSG_SIZE]{};
    read(buff, MAX_MSG_SIZE);
    return {buff};
}


inline  void sockstream::empty()
{
    memset(__buff, 0, __buff_sz);
    __buff_sz = 0;
}


inline void sockstream::send()
{
    int fd;

    switch (__mode)
    {
    case SERVER:
        fd = __client_fd;
        break;
    case CLIENT:
        fd = __fd;
        break;
    case UNSET:
        // TODO: throw some sjit
        break;
    }

    if (write(fd, __buff, __buff_sz) == -1)
            throw std::runtime_error("Writing to socket failed.");
}

/*
 * 
 * STREAM OPERATORS
 * 
 */

sockstream &sockstream::operator<<(std::string const &str)
{ put(str); return *this; }


sockstream &sockstream::operator<<(char c)
{ put(c); return *this; }


sockstream &sockstream::operator>>(std::string &str)
{ read(str); return *this; }


sockstream &sockstream::operator<<(sockstream_op_t op)
{ op(*this); return *this; }


sockstream &sockstream::operator<<(short i)
{
    put(std::to_string(i));
    return *this;
}


sockstream &sockstream::operator<<(int   i)
{
    put(std::to_string(i));
    return *this; 
}


sockstream &sockstream::operator<<(long  i)
{
    put(std::to_string(i));
    return *this;
}



sockstream &sockstream::operator<<(unsigned short i)
{
    put(std::to_string(i));
    return *this;
}


sockstream &sockstream::operator<<(unsigned int  i)
{
    put(std::to_string(i));
    return *this;
}


sockstream &sockstream::operator<<(unsigned long i)
{
    put(std::to_string(i));
    return *this;
}



sockstream &sockstream::operator<<(float       i)
{
    put(std::to_string(i));
    return *this;
}


sockstream &sockstream::operator<<(double      i)
{
    put(std::to_string(i));
    return *this;
}


sockstream &sockstream::operator<<(long double i)
{
    put(std::to_string(i));
    return *this;
}


/*
 * 
 * STREAM OPERATIONS
 * 
 */


void flush(sockstream &ss)
{ ss.send(); ss.empty(); }


void newline(sockstream &ss)
{ ss.put('\n'); }


void endl(sockstream &ss)
{ ss.put('\n'); ss.send(); ss.empty(); }

sockstream_server::sockstream_server(int port)
    :__fd{-1}, __client_fd{-1}, __addr{}

{
    __fd = socket(AF_INET, SOCK_STREAM, 0);
    if (__fd < 0)
        throw std::runtime_error("Failed to create socket file descriptor.");
    
    int opt = 1;
    if (setsockopt(__fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        throw std::runtime_error("Failed to set socket options.");


    bzero(&__addr, sizeof(__addr));

    __addr.sin_family = AF_INET;
    __addr.sin_addr.s_addr = INADDR_ANY;
    __addr.sin_port = htons(port);

    if (bind(__fd, (sockaddr *)&__addr, sizeof(__addr)) < 0)
        throw std::runtime_error("Failed to bind the socket");

    if (listen(__fd, 3) < 0)
        throw std::runtime_error("Failed to start listening.");

    if ((__client_fd = accept(__fd, NULL, NULL)) < 0)
        throw std::runtime_error("Failed to accept a new connecting client.");

}



sockstream_server::~sockstream_server()
{
    close(__fd);
    close(__client_fd);
}

sockstream_server &sockstream_server::operator>>(std::string &str)
{
    char buff[1024];

    memset(buff, 0, 1024);

    if (read(__client_fd, buff, 1024) == -1)
        throw std::runtime_error("Failed to read incoming message.");

    str = buff;

    return *this;
}

} // NAMESPACE CC
