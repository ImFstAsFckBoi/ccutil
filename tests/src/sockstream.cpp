#include "catch2/catch_all.hpp"
#include "ccutil/sockstream.hpp"
#include <pthread.h>
#include <unistd.h>

// This test is pretty bad but it works

void *ccon(void *ss)
{
    sleep(1);
    ((cc::sockstream *)ss)->connect("127.0.0.1", 1111);
    return NULL;
}

void *ccon2(void *ss)
{
    sleep(1);
    ((cc::sockstream *)ss)->connect("127.0.0.1", 2222);
    return NULL;
}



void *ccon6(void *ss)
{
    sleep(1);
    ((cc::sockstream *)ss)->connect("::1", 3333);
    return NULL;
}


void *ccon26(void *ss)
{
    sleep(1);
    ((cc::sockstream *)ss)->connect("::1", 4444);
    return NULL;
}

TEST_CASE("Sockstream")
{
    SECTION("TCP + IPv4")
    {
        cc::sockstream sss{cc::sockstream::TCP, cc::sockstream::IPv4};
        cc::sockstream ssc{cc::sockstream::TCP, cc::sockstream::IPv4};

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

    SECTION("UDP + IPv4")
    {
        cc::sockstream sss{cc::sockstream::UDP, cc::sockstream::IPv4};
        cc::sockstream ssc{cc::sockstream::UDP, cc::sockstream::IPv4};

        pthread_t id;
        pthread_create(&id, NULL, ccon2, &ssc);
        sss.bind(2222);
        pthread_join(id, NULL);

        std::string in_msg;
        
        ssc << "Joe" << cc::flush;
        sss >> in_msg;
        sss << in_msg << " Biden!" << cc::flush;
        ssc >> in_msg;

        REQUIRE(in_msg == "Joe Biden!");
    }
}
