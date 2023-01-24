#pragma once

#include "exception.hpp"
#include "operand.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <stdexcept>

#ifndef MAX_MSG_SIZE
#define MAX_MSG_SIZE 1024
#endif

namespace cc
{

/**
 * @brief Stream object connected to a POSIX socket. 
 * Read and write over the network like if it was cin and cout.
 * Use bind() to create a server socket and connect() to connect a client to a server().
 * \b #define \b MAX_MSG_SIZE to set max message size in bytes. Default is 1024
 * 
 */
class tcpstream
{
private:
    // Private types
    enum __mode_t : uint8_t { UNSET, CLIENT, SERVER };

public:
    // Public types
    enum transport_protocol { TCP, UDP };
    enum network_protocol { IPv4, IPv6 };

    // CTOR, DTOR, ASSIGN
    
    /**
     * @brief Construct a new, uninitialized, tcpstream object with default parameters.
     * Those parameters are TCP over IPv4
     * 
     */
    tcpstream();
    /**
     * @brief Destroy the tcpstream object.
     *
     */
    ~tcpstream();

    tcpstream(const tcpstream &) = delete;
    tcpstream &operator=(const tcpstream &) = delete;

    // CONNECTIONS

    /**
     * @brief Initiate tcpstream object as a client and connect to a server endpoint.
     * 
     * @param addr The address to connect to in string form.
     * @param port TCP port to connect to.
     */
    void connect(std::string const &addr, int port);
    /**
     * @brief Initiate tcpstream object as server and bind to an address and port.
     * 
     * @param addr The address to bind to in string form.
     * @param port TCP port to bind to.
     */
    void bind(std::string const &addr, int port);
    /**
     * @brief Initiate tcpstream object as server and bind to a port.
     * Binds to address "0.0.0.0" i.e. any address in allowed to connect.
     * 
     * @param port TCP port to bind to.
     */
    void bind(int port);

    // BUFFER MANIPULATORS

    /**
     * @brief Put a char \b c into the buffer.
     *
     * @param c Char to add to the buffer.
     */
    void put(char c);
    /**
     * @brief Put a null-terminated c-string into the buffer.
     * 
     * @param cstr Null-terminated c-string.
     */
    void put(char *cstr);
    /**
     * @brief Put a string \b str into the buffer.
     *
     * @param str String to add to the buffer.
     */
    void put(std::string const &str);
    /**
     * @brief Read from the socket add put content into the buffer \b buff.
     *
     * @param buff Buffer to put characters read into.
     * @param buff_len size of \b buffer
     * @return size_t number of bytes received.
     */
    ssize_t read(char *buff, size_t buff_len) const;
    /**
     * @brief Read from the socket into string \b str_buff.
     *
     * @param str_buff string to use as a buffer.
     */
    void read(std::string &str_buff) const;
    /**
     * @brief Read from socket and return contents in a string.
     *
     * @return std::string string containing contents of the socket.
     */
    std::string read() const;
    /**
     * @brief Empty the buffer, without sending.
     *
     */
    void empty();
    /**
     * @brief Send the contents of the buffer, without emptying it.
     *
     */
    void send() const;

    // STREAM OPERATIONS

    /**
     * @brief Write a string to the buffer.
     * 
     * @param str string to write
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(std::string const &str);
    /**
     * @brief Write char to the buffer.
     * 
     * @param c char to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(char c);
    /**
     * @brief Write short to buffer.
     * 
     * @param i short to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(short i);
    /**
     * @brief Write int to buffer.
     * 
     * @param i int to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(int i);
    /**
     * @brief Write long to buffer.
     * 
     * @param i long to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(long i);
    /**
     * @brief Write ushort to buffer.
     * 
     * @param i ushort to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(unsigned short i);
    /**
     * @brief Write uint to buffer.
     * 
     * @param i uint to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(unsigned int i);
    /**
     * @brief Write ulong to buffer.
     * 
     * @param i ulong to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(unsigned long i);
    /**
     * @brief Write float to buffer.
     * 
     * @param i float to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(float i);
    /**
     * @brief Write double to buffer.
     * 
     * @param i double to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(double i);
    /**
     * @brief Write long double to buffer.
     * 
     * @param i long double to write.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(long double i);
    /**
     * @brief Read message from socket into a string.
     * 
     * @param str string to hold incoming message.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator>>(std::string &str);
    /**
     * @brief Read character from the socket.
     * 
     * @param c char to hold incoming character.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator>>(char &c);
    /**
     * @brief Apply functions to the stream. Such as flush and endl.
     * 
     * @param op function to be run.
     * @return tcpstream& reference to input to chain operations.
     */
    tcpstream &operator<<(tcpstream_op_t op);

private:
    __mode_t __mode;
    int __domain;
    int __fd, __client_fd;
    char *__buff;
    size_t __buff_sz;
};

} // NAMESPACE CC
