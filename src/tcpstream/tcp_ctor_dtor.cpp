#include "tcpstream/tcpstream.hpp"
#include <unistd.h>

namespace cc
{

/*
 *
 * CTOR, DTOR
 *
 */

tcpstream::tcpstream()
    : __mode{UNSET}, __domain{AF_INET}, __fd{-1}, __client_fd{-1}, __buff{new char[MAX_MSG_SIZE]}, __buff_sz{0}
{
    __fd = socket(AF_INET, SOCK_STREAM, 0);
    if (__fd < 0)
        throw tcpstream_exception(tcpstream_exception::CREATE_FD);
}

tcpstream::~tcpstream()
{
    close(__fd);
    delete[] __buff;
}

} // NAMESPACE CC
