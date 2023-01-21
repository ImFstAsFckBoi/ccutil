#include "sockstream/sockstream.hpp"

namespace cc
{

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
