#include "catch2/catch_all.hpp"
#include "ccutil/dbv.hpp"
#include <cstdio>

struct test {
    int a;
    float b;
    bool c;
};

struct test2 {
    int arr[3];
    test nest;
};

TEST_CASE("DBV")
{
    SECTION("SIMPLE")
    {
        int value = 0x00C0FFEE;
        {
            cc::dbv<int32_t> test_int{"./test_simple"};
            test_int.set(value);
        }

        {
            cc::dbv<int32_t> test_int{"./test_simple"};
            printf("%d\n", test_int.get());
            REQUIRE(test_int.get() == value);
        }
    }

    SECTION("STRUCT")
    {
        test value = {21, 13.37, true};
        {
            cc::dbv<test> test_int{"./test_struct"};
            test_int.store(value);
        }

        {
            cc::dbv<test> test_int{"./test_struct"};
            REQUIRE(test_int.get().a == value.a);
            REQUIRE(test_int.get().b == value.b);
            REQUIRE(test_int.get().c == value.c);
        }
    }

    SECTION("STRUCT NESTED")
    {
        test2 value = {{1, 2, 3}, {21, 13.37, true}};
        {
            cc::dbv<test2> test_int{"./test_struct_nest"};
            test_int.store(value);
        }

        {
            cc::dbv<test2> test_int{"./test_struct_nest"};
            REQUIRE(test_int.get().arr[0] == value.arr[0]);
            REQUIRE(test_int.get().arr[1] == value.arr[1]);
            REQUIRE(test_int.get().arr[2] == value.arr[2]);
            REQUIRE(test_int.get().nest.a == value.nest.a);
            REQUIRE(test_int.get().nest.b == value.nest.b);
            REQUIRE(test_int.get().nest.c == value.nest.c);
        }
    }

    SECTION("SYNC FREQ")
    {
        int value = 3;
        size_t freq = 3;
        {
            cc::dbv<int> test_int{"./test_freq", freq};
            test_int.set(1);
            test_int.set(2);
            test_int.set(3);
            test_int.set(4);
            test_int.store_on_dtor = false;
        }

        {
            cc::dbv<int> test_int{"./test_freq"};
            REQUIRE(test_int.get() == value);
        }
    }
}
