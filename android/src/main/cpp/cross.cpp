#include <jni.h>
#include <string>
#include "url_signature.h"

JavaVM *jvm = nullptr;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jvm = vm;
    return JNI_VERSION_1_6;
}

void GetJNIEnv(JNIEnv *&env) {
    int status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    // 获取当前native线程是否有没有被附加到jvm环境中
    if (status == JNI_EDETACHED) {
        // 如果没有， 主动附加到jvm环境中，获取到env
        if (jvm->AttachCurrentThread(&env, nullptr) != JNI_OK) {
            // Failed to attach
        }
    } else if (status == JNI_OK) {
        // success
    } else if (status == JNI_EVERSION) {
        // GetEnv: version not supported
    }
}

void test() {
    JNIEnv *env;
    GetJNIEnv(env);
    jstring jstr = env->NewStringUTF("hello world");
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_cross_Cross_signatureUrl(JNIEnv *env, jclass clazz, jstring j_url) {
    const char *url = env->GetStringUTFChars(j_url, JNI_FALSE);
    auto result = env->NewStringUTF(SignatureUrl(url).c_str());
    env->ReleaseStringUTFChars(j_url, url);
    return result;
}