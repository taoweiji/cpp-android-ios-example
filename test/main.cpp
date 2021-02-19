#include <iostream>
#include "json/json.h"
#include "md5.h"

int main() {
    Json::Value json;
    json["name"] = "Wiki";
    json["age"] = 18;
    std::cout << json.toStyledString() << std::endl;
    MD5 md5;
    md5.add("hello",5);
    std::cout << md5.getHash() << std::endl;
    md5.reset();
    std::cout << md5.getHash() << std::endl;
    return 0;
}
