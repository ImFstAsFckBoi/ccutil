#include "tcpstream/tcpstream.hpp"

namespace cc
{

/*
 * 
 * STREAM OPERATORS
 * 
 */

tcpstream &tcpstream::operator<<(std::string const &str)
{ put(str); return *this; }


tcpstream &tcpstream::operator<<(char c)
{ put(c); return *this; }


tcpstream &tcpstream::operator<<(tcpstream_op_t op)
{ op(*this); return *this; }


tcpstream &tcpstream::operator<<(short i)
{
    put(std::to_string(i));
    return *this;
}


tcpstream &tcpstream::operator<<(int   i)
{
    put(std::to_string(i));
    return *this; 
}


tcpstream &tcpstream::operator<<(long  i)
{
    put(std::to_string(i));
    return *this;
}



tcpstream &tcpstream::operator<<(unsigned short i)
{
    put(std::to_string(i));
    return *this;
}


tcpstream &tcpstream::operator<<(unsigned int  i)
{
    put(std::to_string(i));
    return *this;
}


tcpstream &tcpstream::operator<<(unsigned long i)
{
    put(std::to_string(i));
    return *this;
}



tcpstream &tcpstream::operator<<(float       i)
{
    put(std::to_string(i));
    return *this;
}


tcpstream &tcpstream::operator<<(double      i)
{
    put(std::to_string(i));
    return *this;
}


tcpstream &tcpstream::operator<<(long double i)
{
    put(std::to_string(i));
    return *this;
}

} // NAMESPACE CC
