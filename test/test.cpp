#include "gtest/gtest.h"
#include "url_signature.h"

int add(int a, int b) {
    return a + b;
}

TEST(SuiteName, TestName1) {
    int expected = 3;
    int actual = add(1, 2);
    ASSERT_EQ(expected, actual);
}

TEST(SuiteName, TestName2) {
    std::string url = "https://example.com?key2=value2&key3=value3&key1=VALUE1";
    std::string expected = "https://example.com?key2=value2&key3=value3&key1=VALUE1&sign=5779f1cd4693e8b3c5981d37d20aa331";
    std::string actual = SignatureUrl(url);
    ASSERT_EQ(expected, actual);
}