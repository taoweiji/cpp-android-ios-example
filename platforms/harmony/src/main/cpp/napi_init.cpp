#include "napi/native_api.h"
#include "url_signature.h"

static napi_value Add(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    std::string str = SignatureUrl("");

    return sum;
}

static std::string value2String(napi_env env, napi_value value) {
    size_t stringSize = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &stringSize); // 获取字符串长度
    char buff[stringSize + 1];
    napi_get_value_string_utf8(env, value, buff, stringSize + 1, &stringSize); // 根据长度传换成字符串
    return buff;
}

static napi_value SignatureUrl(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    napi_value str = args[0];                         // args[0]->string
    std::string stringValue = value2String(env, str); // 将 str 转换成 string 类型
    std::string result = SignatureUrl(stringValue);
    napi_value sum;
    napi_create_string_utf8(env, result.c_str(), result.length(), &sum);
    return sum;
}


EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"signatureUrl", nullptr, SignatureUrl, nullptr, nullptr, nullptr, napi_default, nullptr}};
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "cross",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterHarmonyModule(void) { napi_module_register(&demoModule); }
