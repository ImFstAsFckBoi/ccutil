#include "str.hpp"

// str is not a reference since it needs to be copied anyway
// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c

namespace cc {


std::vector<std::string> split(std::string str, char delim, std::size_t depth)
{

    std::size_t pos;
    std::vector<std::string> out;
    if (!depth)
        depth = -1;

    while ((pos = str.find(delim)) != std::string::npos && depth--) 
    {
        out.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }

    if (str.size())
        out.push_back(str);

    return out;
}


/* 
 * String trim
 * https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
 */

constexpr char WHITESPACE[7] = " \n\r\t\f\v";

std::string ltrim_cpy(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}


std::string rtrim_cpy(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return end == std::string::npos ? "" : s.substr(0, end + 1);
}


std::string trim_cpy(const std::string &s) {
    return rtrim_cpy(ltrim_cpy(s));
}


std::string &ltrim(std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    s = s.substr(start);
    return s;
}


std::string &rtrim(std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    s = s.substr(0, end + 1);
    return s;
}


std::string &trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
    return s;
}

} // NAMESPACE CC
