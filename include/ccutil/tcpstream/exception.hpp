#pragma once

#include <string>

namespace cc {

/**
 * @brief tcpstream exception class
 * 
 */
class tcpstream_exception : public std::exception
{
public:
    enum tcpstream_except_t
    {
        CREATE_FD, UNSET,   SET,
        ADDR_CON,  CONNECT, OPT,
        BIND,      LISTEN,  ACCEPT,
        BUFF,      READ,    WRITE
    };

    tcpstream_exception(tcpstream_except_t type);
    const char *what() const throw();
private:
    tcpstream_except_t __type;
    std::string __msg;
};

} // NAMESPACE CC
