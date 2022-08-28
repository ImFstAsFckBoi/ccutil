#include "sockstream.hpp"

#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <cstdlib>


namespace cc
{

/*
    * SOCKET EXCEPTION
    *
    */

socket_exception::socket_exception(socket_exception::sock_except_t type)
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

const char *socket_exception::what() const throw()
{
    return __msg.c_str();
}

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
        throw socket_exception(socket_exception::CREATE_FD);
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
        throw socket_exception(socket_exception::SET);

    __mode = CLIENT;

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // inet_pton() return 1 for success and 0 for failure (WHAT)
    if (!inet_pton(AF_INET, _str_addr.c_str(), &addr.sin_addr))
        throw socket_exception(socket_exception::ADDR_CON);

    if (::connect(__fd, (sockaddr *)&addr, sizeof(addr)))
        throw socket_exception(socket_exception::CONNECT);
}

void sockstream::bind(std::string const &str_addr, int port)
{

    sockaddr_in addr;

    std::string _str_addr = (str_addr == "localhost" ? "127.0.0.1" : str_addr);

    if (__mode != UNSET)
        throw socket_exception(socket_exception::SET);

    __mode = SERVER;

    int opt = 1;
    if (setsockopt(__fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        throw socket_exception(socket_exception::OPT);

    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;

    if (!inet_pton(AF_INET, _str_addr.c_str(), &addr.sin_addr))
        throw socket_exception(socket_exception::ADDR_CON);

    addr.sin_port = htons(port);

    if (::bind(__fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        throw socket_exception(socket_exception::BIND);

    if (listen(__fd, 3) < 0)
        throw socket_exception(socket_exception::LISTEN);

    if ((__client_fd = accept(__fd, NULL, NULL)) < 0)
        throw socket_exception(socket_exception::ACCEPT);
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
    if (__buff_sz + 1 > MAX_MSG_SIZE)
    {
        throw socket_exception(socket_exception::BUFF);
    }

    __buff[__buff_sz++] = c;
}


void sockstream::put(char *cstr)
{
    size_t len = strlen(cstr);

    if (__buff_sz + len > MAX_MSG_SIZE)
    {
        throw socket_exception(socket_exception::BUFF);
    }

    memcpy(__buff + __buff_sz, cstr, len);
    __buff_sz += len;
}

void sockstream::put(std::string const &str)
{
    if (str.size() + __buff_sz > MAX_MSG_SIZE)
    {
        throw socket_exception(socket_exception::BUFF);
    }

    memcpy(__buff + __buff_sz, str.data(), str.size());
    __buff_sz += str.size();
}

ssize_t sockstream::read(char *buff, size_t buff_len) const
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
        throw socket_exception(socket_exception::UNSET);
    }

    i = ::read(fd, buff, buff_len);
    if (i == -1)
        throw socket_exception(socket_exception::READ);

    return i;
}

void sockstream::read(std::string &str_buff) const
{
    char buff[MAX_MSG_SIZE]{};
    read(buff, MAX_MSG_SIZE);
    str_buff = buff;
}

std::string sockstream::read() const
{
    char buff[MAX_MSG_SIZE]{};
    read(buff, MAX_MSG_SIZE);
    return {buff};
}

inline void sockstream::empty()
{
    memset(__buff, 0, __buff_sz);
    __buff_sz = 0;
}

void sockstream::send() const
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
        throw socket_exception(socket_exception::UNSET);
        break;
    }

    if (write(fd, __buff, __buff_sz) == -1)
        throw socket_exception(socket_exception::WRITE);
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
 * READ
 * 
 */


sockstream &sockstream::operator>>(std::string &str)
{ read(str); return *this; }


sockstream &sockstream::operator>>(char &c)
{ read(&c, 1); return *this; }


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


} // NAMESPACE CC
