#include "sockstream/sockstream.hpp"

namespace cc
{

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

} // NAMESPACE CC
