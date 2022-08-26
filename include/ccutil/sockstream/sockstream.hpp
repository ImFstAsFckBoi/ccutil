#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

#ifndef MAX_MSG_SIZE
#define MAX_MSG_SIZE 1024
#endif

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
    enum __mode_t : uint8_t
    {
        UNSET,
        CLIENT,
        SERVER
    };

    struct client
    {
        int num;
        sockaddr addr;
        int fd;
    };

public:
    // CTOR, DTOR, ASSIGN
    /**
     * @brief Construct a new, uninitiated, sockstream object.
     * 
     */
    sockstream();
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
     * @brief Put a string \b str into the buffer.
     *
     * @param str String to add to the buffer.
     */
    void put(std::string const &str);
    /**
     * @brief Put any object with std::to_string() into the buffer.
     * 
     * @tparam T Type of object with std::string() implementation.
     * @param t Object to add to the buffer
     */
    //template <typename T>
    //void put(const T &t);
    /**
     * @brief Read from the socket add put content into the buffer \b buff.
     *
     * @param buff Buffer to put characters read into.
     * @param buff_len size of \b buffer
     * @return size_t number of bytes received.
     */
    ssize_t read(char *buff, size_t buff_len);
    /**
     * @brief Read from the socket into string \b str_buff.
     *
     * @param str_buff string to use as a buffer.
     */
    void read(std::string &str_buff);
    /**
     * @brief Read from socket and return contents in a string.
     *
     * @return std::string string containing contents of the socket.
     */
    std::string read();
    /**
     * @brief Empty the buffer, without sending.
     *
     */
    void empty();
    /**
     * @brief Send the contents of the buffer, without emptying it.
     *
     */
    void send();

    // STREAM OPERATORS
    sockstream &operator<<(std::string const &str);
    sockstream &operator<<(char c);

    sockstream &operator<<(short i);
    sockstream &operator<<(int   i);
    sockstream &operator<<(long  i);
    
    sockstream &operator<<(unsigned short i);
    sockstream &operator<<(unsigned int   i);
    sockstream &operator<<(unsigned long  i);

    sockstream &operator<<(float       i);
    sockstream &operator<<(double      i);
    sockstream &operator<<(long double i);
    

    // template <typename T>
    // sockstream &operator<<(const T &t);
    sockstream &operator>>(std::string &str);
    sockstream &operator<<(sockstream_op_t op);

private:
    __mode_t __mode;
    int __fd, __client_fd;
    char *__buff;
    size_t __buff_sz;
};

class sockstream_server  {
    public:
        sockstream_server(int port);
        ~sockstream_server();
        sockstream_server &operator>>(std::string &str);

    private:
        int __fd, __client_fd;
        sockaddr_in __addr;
        
};

} // NAMESPACE CC

#include "sockstream.tpp"
