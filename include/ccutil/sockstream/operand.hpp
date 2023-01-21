#pragma once

namespace cc {

class sockstream;
using sockstream_op_t = void (*)(sockstream &);

// STREAM OPERANDS

/**
 * @brief Send the buffer contents and empty it. Meant to be used as a stream operator. e.g. sockstream << flush;
 *
 * @param ss The sockstream to operate on.
 */
void flush(sockstream &ss);
/**
 * @brief Add a newline tot the buffer. Meant to be used as a stream operator. e.g. sockstream << newline;
 * 
 * @param ss The sockstream to operate on.
 */
void newline(sockstream &ss);
/**
 * @brief Add newline to the buffer and flush. Meant to be used as a stream operator. e.g. sockstream << flush;
 * 
 * @param ss The sockstream to operate on.
 */
void endl(sockstream &ss);

} // NAMESPACE CC
