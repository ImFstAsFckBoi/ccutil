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
class sockstream
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
     * @brief Construct a new, uninitialized, sockstream object with default parameters.
     * Those parameters are TCP over IPv4
     * 
     */
    sockstream();
    /**
     * @brief Construct a new, uninitialized, sockstream object with simplified options.
     * 
     * @param t_proto Transport-layer protocol to use. Options are 'TCP' or 'UDP'.
     * @param n_proto Network-layer protocol to use. Options are 'IPv4' or 'IPv6'.
     */
    sockstream(transport_protocol t_proto, network_protocol n_proto);
    /**
     * @brief Construct a new, uninitialized, sockstream object with full options
     * 
     * @param domain See socket(2) man page.
     * @param type See socket(2) man page.
     * @param protocol See socket(2) man page.
     */
    sockstream(int domain, int type, int protocol);
    /**
     * @brief Destroy the sockstream object.
     *
     */
    ~sockstream();

    sockstream(const sockstream &) = delete;
    sockstream &operator=(const sockstream &) = delete;

    // CONNECTIONS

    /**
     * @brief Initiate sockstream object as a client and connect to a server endpoint.
     * 
     * @param addr The address to connect to in string form.
     * @param port TCP port to connect to.
     */
    void connect(std::string const &addr, int port);
    /**
     * @brief Initiate sockstream object as server and bind to an address and port.
     * 
     * @param addr The address to bind to in string form.
     * @param port TCP port to bind to.
     */
    void bind(std::string const &addr, int port);
    /**
     * @brief Initiate sockstream object as server and bind to a port.
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
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(std::string const &str);
    /**
     * @brief Write char to the buffer.
     * 
     * @param c char to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(char c);
    /**
     * @brief Write short to buffer.
     * 
     * @param i short to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(short i);
    /**
     * @brief Write int to buffer.
     * 
     * @param i int to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(int i);
    /**
     * @brief Write long to buffer.
     * 
     * @param i long to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(long i);
    /**
     * @brief Write ushort to buffer.
     * 
     * @param i ushort to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(unsigned short i);
    /**
     * @brief Write uint to buffer.
     * 
     * @param i uint to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(unsigned int i);
    /**
     * @brief Write ulong to buffer.
     * 
     * @param i ulong to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(unsigned long i);
    /**
     * @brief Write float to buffer.
     * 
     * @param i float to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(float i);
    /**
     * @brief Write double to buffer.
     * 
     * @param i double to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(double i);
    /**
     * @brief Write long double to buffer.
     * 
     * @param i long double to write.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(long double i);
    /**
     * @brief Read message from socket into a string.
     * 
     * @param str string to hold incoming message.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator>>(std::string &str);
    /**
     * @brief Read character from the socket.
     * 
     * @param c char to hold incoming character.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator>>(char &c);
    /**
     * @brief Apply functions to the stream. Such as flush and endl.
     * 
     * @param op function to be run.
     * @return sockstream& reference to input to chain operations.
     */
    sockstream &operator<<(sockstream_op_t op);

private:
    __mode_t __mode;
    int __domain;
    int __fd, __client_fd;
    char *__buff;
    size_t __buff_sz;
};

} // NAMESPACE CC
