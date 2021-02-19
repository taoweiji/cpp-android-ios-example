#include <iostream>
#include "url_signature.h"
#include <string>

using namespace std;

int main() {
    string url = "http://example.com?key2=value2&key3=value3&key1=VALUE1";
    std::cout << url << std::endl;
    std::cout << SignatureUrl(url) << std::endl;
    return 0;
}
