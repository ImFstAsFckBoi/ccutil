#pragma once

#include <string>

namespace cc {

/**
 * @brief sockstream exception class
 * 
 */
class sockstream_exception : public std::exception
{
public:
    enum sockstream_except_t
    {
        CREATE_FD, UNSET,   SET,
        ADDR_CON,  CONNECT, OPT,
        BIND,      LISTEN,  ACCEPT,
        BUFF,      READ,    WRITE
    };

    sockstream_exception(sockstream_except_t type);
    const char *what() const throw();
private:
    sockstream_except_t __type;
    std::string __msg;
};

} // NAMESPACE CC
