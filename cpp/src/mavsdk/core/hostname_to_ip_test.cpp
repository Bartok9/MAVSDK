#include "hostname_to_ip.hpp"
#include <gtest/gtest.h>

using namespace mavsdk;

TEST(HostnameToIp, Localhost)
{
    auto host = "localhost";
    auto ip = resolve_hostname_to_ip(host);
    ASSERT_TRUE(ip);
    EXPECT_EQ(ip.value(), "127.0.0.1");
}

TEST(HostnameToIp, Ip)
{
    auto host = "127.0.0.1";
    auto ip = resolve_hostname_to_ip(host);
    ASSERT_TRUE(ip);
    EXPECT_EQ(ip.value(), host);
}

TEST(HostnameToIp, Empty)
{
    auto host = "";
    auto ip = resolve_hostname_to_ip(host);
    EXPECT_FALSE(ip);
}

TEST(HostnameToIp, Something)
{
    auto host = "something";
    auto ip = resolve_hostname_to_ip(host);
    EXPECT_FALSE(ip);
}

TEST(HostnameToIp, DottedPrivate)
{
    auto ip = resolve_hostname_to_ip("192.168.1.10");
    ASSERT_TRUE(ip);
    EXPECT_EQ(ip.value(), "192.168.1.10");
}

TEST(HostnameToIp, ZeroZeroZeroZero)
{
    auto ip = resolve_hostname_to_ip("0.0.0.0");
    ASSERT_TRUE(ip);
    EXPECT_EQ(ip.value(), "0.0.0.0");
}

TEST(HostnameToIp, WhitespaceRejected)
{
    EXPECT_FALSE(resolve_hostname_to_ip(" "));
    EXPECT_FALSE(resolve_hostname_to_ip("127.0.0.1 "));
}

TEST(HostnameToIp, BroadcastAndLoopbackVariants)
{
    auto b = resolve_hostname_to_ip("255.255.255.255");
    ASSERT_TRUE(b);
    EXPECT_EQ(b.value(), "255.255.255.255");

    auto loop = resolve_hostname_to_ip("127.0.0.1");
    ASSERT_TRUE(loop);
    EXPECT_EQ(loop.value(), "127.0.0.1");
}

TEST(HostnameToIp, IncompleteDottedRejected)
{
    // Incomplete IPv4-looking strings must not resolve as hostnames spontaneously.
    EXPECT_FALSE(resolve_hostname_to_ip("192.168.1"));
    EXPECT_FALSE(resolve_hostname_to_ip("1.2"));
}
