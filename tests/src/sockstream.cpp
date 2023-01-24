#include "catch2/catch_all.hpp"
#include "ccutil/sockstream.hpp"
#include <pthread.h>
#include <unistd.h>

// This test is pretty bad but it works

void *ccon(void *ss)
{
    sleep(1);
    ((cc::tcpstream *)ss)->connect("127.0.0.1", 1111);
    return NULL;
}

TEST_CASE("Sockstream")
{
    SECTION("TCP")
    {
        cc::tcpstream sss{};
        cc::tcpstream ssc{};

        pthread_t id;
        pthread_create(&id, NULL, ccon, &ssc);
        sss.bind(1111);
        pthread_join(id, NULL);

        std::string in_msg;
        
        ssc << "Joe" << cc::flush;
        sss >> in_msg;
        sss << in_msg << " Biden!" << cc::flush;
        ssc >> in_msg;

        REQUIRE(in_msg == "Joe Biden!");
    }
}
