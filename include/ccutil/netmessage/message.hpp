#pragma once

#include "tcpstream/tcpstream.hpp"

#include <cstdint>
#include <vector>
#include <string>


namespace cc
{

/**
 * @brief Prototype enum class to referencing when interpreting read data.
 * 
 */
enum class MsgType : uint32_t;

using byte_t    = uint8_t;

/**
 * @brief A data container to be sent over a socket or TCP connection
 * and be easily received and read by a recipient sharing the same MsgType enum.
 * 
 */
class Message
{
public:
    /**
     * @brief A header for the message object containing the size of the messages data body and a 
     * MsgType enum for the recipient to referencing when determining how to interpret the sent data.
     * 
     */
    struct MsgHeader
    {
        MsgType msg_type;
        uint32_t body_size;

        friend tcpstream &operator>>(tcpstream &s, const MsgHeader &header);
        friend tcpstream &operator<<(tcpstream &s, MsgHeader &header);

    };

    using MsgBody = std::vector<byte_t>;
    /**
     * @brief Default constructor.
     * 
     */
    Message() noexcept;
    /**
     * See message.tcc for description.
     */
    template<typename T>
    Message(MsgType type, const std::vector<T> &body);
    /**
     * @brief A specialized constructor for strings. 
     * More convenient that using Message(MsgType type, const std::vector<T> &body) with vector<char>.
     * 
     * @param type Message type. Has no implicit meaning. Meant to be used by receiver to know what the message is, what data type to cast to, etc.
     * @param s The string that will be the body of the Message. Will be converted into vector<byte_t> internally.
     */
    Message(MsgType type, const std::string &s);
    /**
     * @brief A move constructor. Moves the body vector to new object.
     * 
     * @param cpy rvalue object to copy.
     */
    Message(Message &&cpy);
    /**
     * See message.tcc for description.
     */
    template<typename T>
    std::vector<T> copy_data_as() const;
    /**
     * See message.tcc for description.
     */
    template<typename T>
    std::vector<T> &get_data_as();
    /**
     * See message.tcc for description.
     */
    template<typename T>
    const std::vector<T> &get_data_as() const;
    /**
     * See message.tcc for description.
     */
    template<typename T>
    void place_data_as(std::vector<T> &buffer, bool resize) const;
    /**
     * See message.tcc for description.
     */
    template<typename T>
    void place_data_as(std::vector<T> &buffer) const;
    /**
     * @brief Const getter for the header.
     * 
     * @return const MsgHeader& 
     */
    const MsgHeader &header() const noexcept;
    /**
     * @brief Const getter for the body.
     * 
     * @return const MsgHeader& 
     */
    const MsgBody &body() const noexcept;
    /**
     * @brief Getter for the body.
     * 
     * @return MsgHeader& 
     */
    MsgHeader &header() noexcept;
    /**
     * @brief Getter for the header.
     * 
     * @return MsgBody& 
     */
    MsgBody &body() noexcept;
    /**
     * @brief Push the message msg into a socket to be written.
     * 
     * @param s cc::tcpstream connection to write to.
     * @param msg Message to be written to the socket.
     * @return cc::tcpstream& reference to s socket object to chain writes like std::cout.
     */
    friend tcpstream &operator<<(tcpstream &s, const Message &msg);
    /**
     * @brief Read an incoming message into msg.
     * 
     * @param s cc::tcpstream connection to read from.
     * @param msg Object where the read message will be stored.
     * @return cc::tcpstream& reference to s socket object to chain reads like std::cin.
     */
    friend tcpstream &operator>>(tcpstream &s, Message &msg);


private:
    MsgHeader _header;
    MsgBody   _body;
};


} // NAMESPACE CC

#include "message.tcc"

