#include "sockstream/sockstream.hpp"

namespace cc
{

/*
 * READ
 * 
 */


sockstream &sockstream::operator>>(std::string &str)
{ read(str); return *this; }


sockstream &sockstream::operator>>(char &c)
{ read(&c, 1); return *this; }

} // NAMESPACE CC
