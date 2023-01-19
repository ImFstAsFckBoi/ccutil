#include "ccutil/zip.hpp"
#include "catch2/catch_all.hpp"

#include <sstream>
#include <vector>
#include <string>
#include <map>

TEST_CASE("Zip")
{
    SECTION("iter with diff len")
    {
        std::stringstream ss;
        std::vector<int> v{1, 2, 3};
        std::string s{"abcde"};
        for (auto i : cc::zip(v, s))
        {
            ss << i.first << i.second;
        }

        REQUIRE(ss.str() == "1a2b3c");

        ss.str("");

        for (auto i : cc::zip(s, v))
        {
            ss << i.first << i.second;
        }

        REQUIRE(ss.str() == "a1b2c3");
    }

    SECTION("complex types")
    {
        std::stringstream ss;
        std::vector<std::string> v{"1www", "2abc",  "3xyz"};
        std::map<std::string, std::vector<int>> m{{"1www", {9, 8, 5}}, {"2abc", {1, 2, 3}}, {"3xyz", {6, 6, 6}}};

        for (auto i : cc::zip(v, m))
        {
            if (i.first == i.second.first)
            {
                for (auto j: i.second.second)
                {
                    ss << j;
                }
            }
        }

        REQUIRE(ss.str() == "985123666");
    }

    SECTION("zero len")
    {
        int C = 0;
        std::vector<int> v{};
        std::string s{"abc"};
        for (auto i : cc::zip(v, s))
        {
            C++; // lol
        }

        REQUIRE(C == 0);
    }
}
