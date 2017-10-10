#include <jni.h>

#ifndef _Included_FAAD2
#define _Included_FAAD2
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_faad2_EasyDecoder_decode
  (JNIEnv *, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_faad2_EasyDecoder_init
  (JNIEnv *, jobject);
JNIEXPORT jint JNICALL Java_faad2_EasyDecoder_getError
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
