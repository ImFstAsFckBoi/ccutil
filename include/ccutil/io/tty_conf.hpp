#include <termios.h>
#include <unistd.h>
#include <stdio.h>

namespace cc {
class tty_conf
{
public:
	tty_conf(int fd = STDIN_FILENO);
	~tty_conf();
	void apply();
	void reset();

	void set_input(tcflag_t tcflag);
	void unset_input(tcflag_t tcflag);
	void toggle_input(tcflag_t tcflag);

	void set_output(tcflag_t tcflag);
	void unset_output(tcflag_t tcflag);
	void toggle_output(tcflag_t tcflag);

	void set_contorl(tcflag_t tcflag);
	void unset_contorl(tcflag_t tcflag);
	void toggle_contorl(tcflag_t tcflag);

	void set_local(tcflag_t tcflag);
	void unset_local(tcflag_t tcflag);
	void toggle_local(tcflag_t tcflag);
private:
	int __fd;
	struct termios __cur;
	struct termios __old;
};

}
