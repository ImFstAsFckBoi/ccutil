#include "tcpstream/tcpstream.hpp"

namespace cc
{

/*
 * 
 * STREAM OPERATIONS
 * 
 */


void flush(tcpstream &ss)
{ ss.send(); ss.empty(); }


void newline(tcpstream &ss)
{ ss.put('\n'); }


void endl(tcpstream &ss)
{ ss.put('\n'); ss.send(); ss.empty(); }

} // NAMESPACE CC
