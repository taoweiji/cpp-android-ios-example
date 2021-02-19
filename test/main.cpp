#include <iostream>
#include "json/json.h"

int main() {
    Json::Value json;
    json["name"] = "Wiki";
    json["age"] = 18;
    std::cout << json.toStyledString() << std::endl;
    return 0;
}
