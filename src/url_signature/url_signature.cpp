//
// Created by Wiki on 2021/2/18.
//

#include "url_signature.h"
#include <cxxurl/url.hpp>
#include <algorithm>
#include <md5.h>
#include <map>

using namespace std;
const string SIGNATURE_URL_SECRET = "1bc29b36f623ba82aaf6724fd3b16718";

string SignatureUrl(const string &url) {
    Url u(url);
    map<string, string> params;
    vector<string> keys;
    for (int i = 0; i < u.query().size(); ++i) {
        Url::KeyVal keyVal = u.query(i);
        keys.push_back(keyVal.key());
        params[keyVal.key()] = keyVal.val();
    }
    // 排序
    sort(keys.begin(), keys.end());
    string str;
    for (auto &key : keys) {
        str += key;
        str += params[key];
    }
    // 拼接密钥到字符串的后面
    str += SIGNATURE_URL_SECRET;
    // 转成小写
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    // 计算md5
    MD5 md5;
    md5.reset();
    md5.add(str.c_str(), str.length());
    // 添加md5到url
    u.add_query("sign", md5.getHash());
    return u.str();
}