#include <jni.h>
#include <string>
#include "url_signature.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cross_Cross_signatureUrl(JNIEnv *env, jclass clazz, jstring url) {
    const char *str = env->GetStringUTFChars(url, JNI_FALSE);
    std::string result = SignatureUrl(str);
    return env->NewStringUTF(result.c_str());
}