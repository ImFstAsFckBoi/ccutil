#include "catch2/catch.hpp"
#include "ccutil/sockstream.hpp"
#include <pthread.h>
#include <unistd.h>

// This test is pretty bad but it works

void *ccon(void *ss)
{
    sleep(1);
    ((cc::sockstream *)ss)->connect("127.0.0.1", 6969);
    return NULL;
}

TEST_CASE("Sockstream")
{
    SECTION("Basic Send & Receive")
    {
        cc::sockstream sss;
        cc::sockstream ssc;

        pthread_t id;
        pthread_create(&id, NULL, ccon, &ssc);
        sss.bind(6969);
        pthread_join(id, NULL);

        std::string in_msg;
        
        ssc << "Joe" << cc::flush;
        sss >> in_msg;
        sss << in_msg << " Biden!" << cc::flush;
        ssc >> in_msg;

        REQUIRE(in_msg == "Joe Biden!");
    }
}
