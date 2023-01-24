#pragma once

namespace cc {

class tcpstream;
using tcpstream_op_t = void (*)(tcpstream &);

// STREAM OPERANDS

/**
 * @brief Send the buffer contents and empty it. Meant to be used as a stream operator. e.g. tcpstream << flush;
 *
 * @param ss The tcpstream to operate on.
 */
void flush(tcpstream &ss);
/**
 * @brief Add a newline tot the buffer. Meant to be used as a stream operator. e.g. tcpstream << newline;
 * 
 * @param ss The tcpstream to operate on.
 */
void newline(tcpstream &ss);
/**
 * @brief Add newline to the buffer and flush. Meant to be used as a stream operator. e.g. tcpstream << flush;
 * 
 * @param ss The tcpstream to operate on.
 */
void endl(tcpstream &ss);

} // NAMESPACE CC
