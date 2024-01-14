#pragma once

#include "message.hpp"

#include <stdexcept>
#include <sstream>
#include <cstring>

namespace cc
{
    


/**
 * @brief [INTERNAL] Checks if amounts bytes fits evenly into type T
 * 
 * @tparam T Type to fit into
 * @param bytes Amount of bytes
 */
template<typename T>
inline void __CHECK_SIZE_MATCH(std::size_t bytes)
{
    if (bytes % sizeof(T) != 0)
    {
        std::stringstream ss{};
        ss << "The amount of bytes (" << bytes << ") does not fit evenly into type " << typeid(T).name() << " with a size of " << sizeof(T);
        throw std::logic_error(ss.str().c_str());
    }
}

/**
 * MESSAGE METHODS
 * 
 */



/**
 * @brief Construct a new Message object.
 * 
 * @tparam T Type of primitive data. Classes with managed memory will not work if sent over a socket.
 * Define MSG_ALLOW_NON_PRIMITIVE to enable non primitives, but do so att your own risk.
 * @param type Message type. Has no implicit meaning. Meant to be used by receiver to know what the message is, what data type to cast to, etc.
 * @param body A vector of data to act as the body of the message. will be converted into vector<byte_t> internally.
 */
template<typename T>
cc::Message::Message(MsgType type, const std::vector<T> &body)
    : _header{type, static_cast<uint32_t>(body.size() * sizeof(T))}, _body(sizeof(T)* body.size())
{ 
    #ifndef MSG_ALLOW_NON_PRIMITIVE
    static_assert(std::is_standard_layout<T>::value);
    #endif

    // copy the data from body into _body
    // done with memcpy to force all datatypes T into byte_t
    std::memcpy(_body.data(), body.data(), _body.size());
}
/**
 * @brief Cast the data contained in the message as bytes into a vector<T>.
 * The casting is unsafe and is done with pure memory with std::memcpy().
 * Define @b MSG_ALLOW_NON_PRIMITIVE to enable non primitives, but do so att your own risk.
 * @tparam T Datatype to cast the message body into.
 * @return std::vector<T> of the casted data.
 */
template <typename T>
std::vector<T> Message::copy_data_as() const
{
    // assert that T is a simple type, eg. int, float, or simple struct
    #ifndef MSG_ALLOW_NON_PRIMITIVE
    static_assert(std::is_standard_layout<T>::value);
    #endif

    __CHECK_SIZE_MATCH<T>(_header.body_size);

    // copy the data from the _body vector into the out vector
    std::vector<T> out(_header.body_size / sizeof(T));
    std::memcpy(out.data(), _body.data(), _body.size());
    return out;
}
/**
 * @brief Get a reference straight to the messages body data.
 * 
 * @return std::vector<T>& casted reference
 */
template<typename T>
inline std::vector<T> &Message::get_data_as()
{
    #ifndef MSG_ALLOW_NON_PRIMITIVE
    // assert that T is a simple type, eg. int, float, or simple struct
    static_assert(std::is_standard_layout<T>::value);
    #endif
    __CHECK_SIZE_MATCH<T>(_header.body_size);
    // casts _body to vector<T> type by cirucumventing the type system when casting 
    // its adress (vector<byte_t> *) into a vector<T> * and then dereferences it.
    // out.size() will be correct since std::vector dosent keep track of its size in a variable.
    // this solution might have other unkown issues due to forcefully being casted.
    // inspired by Q_rsqrt() from the Quake III engine
    return *(reinterpret_cast<std::vector<T> *>(&_body));
}
/**
 * @brief Get a const reference straight to the messages body data.
 * 
 * @return const std::vector<T>& casted reference
 */
template<typename T>
inline const std::vector<T> &Message::get_data_as() const
{ 
    #ifndef MSG_ALLOW_NON_PRIMITIVE
    // assert that T is a simple type, eg. int, float, or simple struct
    static_assert(std::is_standard_layout<T>::value);
    #endif
    __CHECK_SIZE_MATCH<T>(_header.body_size);
    // see above function
    return *(reinterpret_cast<const std::vector<T> *>(&_body));
}
/**
 * @brief Place the data into an existing buffer.
 * The casting is unsafe and is done with pure memory with std::memcpy().
 * Define @b MSG_ALLOW_NON_PRIMITIVE to enable non primitives, but do so att your own risk.
 * 
 * @tparam T Datatype to cast the message body into.
 * @param buffer Buffer to place the casted data into.
 * @param resize if true the buffer will be resized to fit all data.
 */
template<typename T>
void Message::place_data_as(std::vector<T> &buffer, bool resize) const
{
    // assert that T is a simple type, eg. int, float, or simple struct
    #ifndef MSG_ALLOW_NON_PRIMITIVE
    static_assert(std::is_standard_layout<T>::value);
    #endif

    __CHECK_SIZE_MATCH<T>(_header.body_size);

    // if resize it will copy the whole body
    // if not it will copy as much as the buffer can hold
    std::size_t sz{sizeof(T) * buffer.size()};
    if (resize)
    {
        buffer.resize(_header.body_size / sizeof(T));
        sz = _body.size();
    }

    // copy the data from the _body vector into the buffer
    std::memcpy(buffer.data(), _body.data(), sz);
}
/**
 * @brief Place as much data possible into an existing buffer. 
 * The casting is unsafe and is done with pure memory with std::memcpy().
 * Define @b MSG_ALLOW_NON_PRIMITIVE to enable non primitives, but do so att your own risk.
 * 
 * @tparam T Datatype to cast the message body into.
 * @param buffer Buffer to place the casted data into.
 */
template<typename T>
void Message::place_data_as(std::vector<T> &buffer) const
{
    #ifndef MSG_ALLOW_NON_PRIMITIVE
    // assert that T is a simple type, eg. int, float, or simple struct
    static_assert(std::is_standard_layout<T>::value);
    #endif

    __CHECK_SIZE_MATCH<T>(_header.body_size);

    // copy the data from the _body vector into the buffer
    std::memcpy(buffer.data(), _body.data(), _body.size() > sizeof(T) * buffer.size() ? sizeof(T) * buffer.size() : _body.size());
}


} // NAMESPACE CC
