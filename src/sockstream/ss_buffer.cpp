#include "sockstream/sockstream.hpp"

#include <cstring>
#include <unistd.h>

namespace cc
{

/*
 *
 * BUFFER MANIPULATORS
 *
 */

void sockstream::put(char c)
{
    if (__buff_sz + 1 > MAX_MSG_SIZE)
    {
        throw sockstream_exception(sockstream_exception::BUFF);
    }

    __buff[__buff_sz++] = c;
}


void sockstream::put(char *cstr)
{
    size_t len = strlen(cstr);

    if (__buff_sz + len > MAX_MSG_SIZE)
    {
        throw sockstream_exception(sockstream_exception::BUFF);
    }

    memcpy(__buff + __buff_sz, cstr, len);
    __buff_sz += len;
}

void sockstream::put(std::string const &str)
{
    if (str.size() + __buff_sz > MAX_MSG_SIZE)
    {
        throw sockstream_exception(sockstream_exception::BUFF);
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
        throw sockstream_exception(sockstream_exception::UNSET);
    }

    i = ::read(fd, buff, buff_len);
    if (i == -1)
        throw sockstream_exception(sockstream_exception::READ);

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

void sockstream::empty()
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
        throw sockstream_exception(sockstream_exception::UNSET);
        break;
    }

    if (write(fd, __buff, __buff_sz) == -1)
        throw sockstream_exception(sockstream_exception::WRITE);
}

} // NAMESPACE CC
