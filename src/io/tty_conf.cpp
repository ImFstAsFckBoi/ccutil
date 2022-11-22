#include "io/tty_conf.hpp"

#include <stdexcept>
namespace cc {

tty_conf::tty_conf(int fd)
    : __fd{fd}, __cur{}, __old{}
{
    if (tcgetattr(fd, &__old))
        throw std::invalid_argument("fd is not a valid file descriptor");

     __cur = __old;


}


tty_conf::~tty_conf()
{
     reset();
}

void tty_conf::apply()
{
    if (tcsetattr(__fd, TCSAFLUSH, &__cur))
        throw std::runtime_error("failed to set tc");
}

void tty_conf::reset()
{
    if (tcsetattr(__fd, TCSAFLUSH, &__old))
        throw std::runtime_error("failed to set tc");

}


void tty_conf::set_input(tcflag_t tcflag)
{ __cur.c_iflag |= tcflag; }
void tty_conf::unset_input(tcflag_t tcflag)
{ __cur.c_iflag &= ~tcflag; }
void tty_conf::toggle_input(tcflag_t tcflag)
{ __cur.c_iflag ^= tcflag; }
void tty_conf::set_output(tcflag_t tcflag)
{ __cur.c_oflag |= tcflag; }
void tty_conf::unset_output(tcflag_t tcflag)
{ __cur.c_oflag &= ~tcflag; }
void tty_conf::toggle_output(tcflag_t tcflag)
{ __cur.c_oflag ^= tcflag; }
void tty_conf::set_contorl(tcflag_t tcflag)
{ __cur.c_cflag |= tcflag; }
void tty_conf::unset_contorl(tcflag_t tcflag)
{ __cur.c_cflag &= ~tcflag; }
void tty_conf::toggle_contorl(tcflag_t tcflag)
{ __cur.c_cflag ^= tcflag; }
void tty_conf::set_local(tcflag_t tcflag)
{ __cur.c_lflag |= tcflag; }
void tty_conf::unset_local(tcflag_t tcflag)
{ __cur.c_lflag &= ~tcflag; }
void tty_conf::toggle_local(tcflag_t tcflag)
{ __cur.c_lflag ^= tcflag; }

}
