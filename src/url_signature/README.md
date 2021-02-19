# URL签名
1. 约定密钥：1bc29b36f623ba82aaf6724fd3b16718
2. http://example.com?key1=VALUE1&key2=value2&key3=value3
3. 对参数的name进行排序后拼接获得 key1VALUE1key2value2key3value3
4. 拼接后的参数+特定的私钥组合成 key1VALUE1key2value2key3value31bc29b36f623ba82aaf6724fd3b16718
5. 对拼接后的参数转换成小写key1value1key2value2key3value31bc29b36f623ba82aaf6724fd3b16718
6. 然后执行md5，得到签名字符串 5779f1cd4693e8b3c5981d37d20aa331
7. 这个签名字符串也需要放到参数后一起请求服务端，http://example.com?key1=VALUE1&key2=value2&key3=value3&sign=5779f1cd4693e8b3c5981d37d20aa331

> 这个是标准URL签名方式，密钥放在服务端和C++代码中，这个密钥不能让外部人员知晓