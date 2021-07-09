#include <jni.h>
#include <string>
#include "url_signature.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cross_Cross_signatureUrl(JNIEnv *env, jclass clazz, jstring j_url) {
    const char *url = env->GetStringUTFChars(j_url, JNI_FALSE);
    auto result = env->NewStringUTF(SignatureUrl(url).c_str());
    env->ReleaseStringUTFChars(j_url, url);
    return result;
}