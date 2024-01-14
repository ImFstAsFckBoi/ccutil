#include "netmessage/message.hpp"

namespace cc {


Message::Message() noexcept
    : _header{}, _body{}
{}

Message::Message(MsgType type, const std::string &s)
    : _header{type, static_cast<byte_t>(s.size())}, _body(s.data(), s.data() + s.size())
{}


Message::Message(Message &&cpy)
    : _header{cpy._header}, _body{std::move(cpy._body)}
{}

inline const Message::MsgHeader &Message::header() const noexcept
{ return _header; }

inline const Message::MsgBody &Message::body() const noexcept
{ return _body; }

inline Message::MsgHeader &Message::header() noexcept
{ return _header; }

inline Message::MsgBody &Message::body() noexcept
{ return _body; }


tcpstream &operator>>(tcpstream &s, const Message::MsgHeader &header)
{
    char buff;
     //[] = "\0\0";
    s >> buff;
    //header.msg_type = atoi(buff);
}


tcpstream &operator<<(tcpstream &s, Message::MsgHeader &header)
{

}


tcpstream &operator<<(tcpstream &s, const Message &msg)
{
   // s.write_some(asio::buffer(&(msg._header), sizeof(Message::MsgHeader)));
    //s.write_some(asio::buffer(msg._body.data(), msg._body.size()));
    return s;
}


tcpstream &operator>>(tcpstream &s, Message &msg)
{
    s >> msg._header;
    //  s.read_some(asio::buffer(&(msg._header), sizeof(Message::MsgHeader)));
    //  msg._body.resize(msg._header.body_size);
    // #ifdef MSG_WAIT_SAFE
    //    s.wait(s.wait_read);
    // #endif
    //   s.read_some(asio::buffer(msg._body.data(), msg._header.body_size));
    return s;
}

} // NAMESPACE CC
