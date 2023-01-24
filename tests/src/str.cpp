#include "catch2/catch_all.hpp"
#include "ccutil/str.hpp"
#include <sstream>

TEST_CASE("Str")
{
    SECTION("basic split")
    {
        std::string s{"a b c$d e f$g h i"};
        std::stringstream ss{};

        auto v1 = cc::split(s, '$');
        REQUIRE(v1.size() == 3);

        for (auto i: v1)
        {
            auto v2 = cc::split(i);
            REQUIRE(v2.size() == 3);
            ss << v2.at(1);
        }

        REQUIRE(ss.str() == "beh");
    }

    SECTION("split depth")
    {
        std::string s{"a-b-c"};

        auto v1 = cc::split(s, '-', 1);
        REQUIRE(v1.size() == 2);
        REQUIRE(v1.at(0) == "a");
        REQUIRE(v1.at(1) == "b-c");
    }

    SECTION("trimming")
    {
        std::string s{"\t abc   \n"};
        auto t = cc::trim_cpy(s);
        cc::trim(s);
        REQUIRE(t == "abc");
        REQUIRE(s == "abc");
    }

    SECTION("ltrim & rtrim")
    {
        std::string s1{"\t abc   \n"};
        cc::ltrim(s1);
        REQUIRE(s1 == "abc   \n");

        std::string s2{"\t abc   \n"};
        cc::rtrim(s2);
        REQUIRE(s2 == "\t abc");

        cc::rtrim(s1);
        cc::ltrim(s2);

        REQUIRE(s1 == "abc");
        REQUIRE(s2 == "abc");
        
    }

    SECTION("ltrim_cpy & rtrim_cpy")
    {
        std::string s1{"\t abc   \n"};
        auto s11 = cc::ltrim(s1);
        REQUIRE(s1 == "abc   \n");

        std::string s2{"\t abc   \n"};
        auto s22 = cc::rtrim(s2);
        REQUIRE(s2 == "\t abc");

        auto s111 = cc::rtrim(s11);
        auto s222 = cc::ltrim(s2);

        REQUIRE(s111 == "abc");
        REQUIRE(s222 == "abc");
        
    }
}
