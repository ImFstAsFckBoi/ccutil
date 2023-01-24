#include "tcpstream/tcpstream.hpp"

namespace cc
{

/*
 * READ
 * 
 */


tcpstream &tcpstream::operator>>(std::string &str)
{ read(str); return *this; }


tcpstream &tcpstream::operator>>(char &c)
{ read(&c, 1); return *this; }

} // NAMESPACE CC
