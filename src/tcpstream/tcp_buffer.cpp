#include "tcpstream/tcpstream.hpp"

#include <cstring>
#include <unistd.h>

namespace cc
{

/*
 *
 * BUFFER MANIPULATORS
 *
 */

void tcpstream::put(char c)
{
    if (__buff_sz + 1 > MAX_MSG_SIZE)
    {
        throw tcpstream_exception(tcpstream_exception::BUFF);
    }

    __buff[__buff_sz++] = c;
}


void tcpstream::put(char *cstr)
{
    size_t len = strlen(cstr);

    if (__buff_sz + len > MAX_MSG_SIZE)
    {
        throw tcpstream_exception(tcpstream_exception::BUFF);
    }

    memcpy(__buff + __buff_sz, cstr, len);
    __buff_sz += len;
}

void tcpstream::put(std::string const &str)
{
    if (str.size() + __buff_sz > MAX_MSG_SIZE)
    {
        throw tcpstream_exception(tcpstream_exception::BUFF);
    }

    memcpy(__buff + __buff_sz, str.data(), str.size());
    __buff_sz += str.size();
}

ssize_t tcpstream::read(char *buff, size_t buff_len) const
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
        throw tcpstream_exception(tcpstream_exception::UNSET);
    }

    i = ::read(fd, buff, buff_len);
    if (i == -1)
        throw tcpstream_exception(tcpstream_exception::READ);

    return i;
}

void tcpstream::read(std::string &str_buff) const
{
    char buff[MAX_MSG_SIZE]{};
    read(buff, MAX_MSG_SIZE);
    str_buff = buff;
}

std::string tcpstream::read() const
{
    char buff[MAX_MSG_SIZE]{};
    read(buff, MAX_MSG_SIZE);
    return {buff};
}

void tcpstream::empty()
{
    memset(__buff, 0, __buff_sz);
    __buff_sz = 0;
}

void tcpstream::send() const
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
        throw tcpstream_exception(tcpstream_exception::UNSET);
        break;
    }

    if (write(fd, __buff, __buff_sz) == -1)
        throw tcpstream_exception(tcpstream_exception::WRITE);
}

} // NAMESPACE CC
