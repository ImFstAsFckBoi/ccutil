/*
    Cant be tested in normal test.
    have to be tested in main.cpp manually

#include "ccutil/io.hpp"
#include <iostream>

int main()
{
    {
        cc::tty_conf tty_c(0);
        tty_c.unset_local(ICANON);
        tty_c.unset_local(ECHO);
        tty_c.apply();
        std::cout << "Type 5 chars" << std::endl;
        for (int i{1}; i < 6; ++i)
        {
            char c = getchar();
            std::cout << "[" << i << "] " << c << std::endl;
        }
        std::cout << "========================" << std::endl;
    }

    std::cout << "Reset\n> ";
    std::string s{};
    std::cin >> s;
    std::cout << "[-] " << s << std::endl;
}

*/
