/*
 * Copyright (c) 2021. Created by : JackyHieu.
 * Support: hieu1211.ictu@gmail.com
 */

#ifndef _Included_vn_hn_tools_Archive
#define _Included_vn_hn_tools_Archive

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Class:     hn_tools_zip_Archive
 * Method:    init
 * Signature: ()V
 */

JNIEXPORT void JNICALL Java_hn_tools_zip_Archive_init
  (JNIEnv * env, jclass cls);

JNIEXPORT void JNICALL Java_hn_tools_zip_Archive_loadAllCodecsAndFormats
  (JNIEnv *, jobject);

JNIEXPORT jlong JNICALL Java_hn_tools_zip_Archive_getRamSize
  (JNIEnv *, jclass cls);
/*
 * Class:     hn_tools_zip_test7zconsole_Archive
 * Method:    print5zInfo
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_hn_tools_zip_Archive_print7zInfo
  (JNIEnv *, jobject);

/*
 * Class:     hn_tools_zip_test7zconsole_Archive
 * Method:    extractArchive
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lcom/mg/test7zconsole/ExtractCallback;)I
 */
JNIEXPORT jint JNICALL Java_hn_tools_zip_Archive_extractArchive
  (JNIEnv *, jobject, jstring, jstring,jobject);

/*
 * Class:     hn_tools_zip_test7zconsole_Archive
 * Method:    createArchive
 * Signature: (Ljava/lang/String;[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_hn_tools_zip_Archive_createArchive
  (JNIEnv *, jobject, jstring, jobjectArray,jint length,jint level,jint dictionary,
		  jint wordSize,jboolean orderMode,jboolean solid,jlong solidBlockSize,jstring method,
		  jstring encryptionMethod,jint findex,
		  jboolean encryptHeaders,jboolean encryptHeadersAllowed,jstring pass
		  ,jboolean multiThread ,jobject callback);

JNIEXPORT jint JNICALL Java_hn_tools_zip_Archive_listArchive
  (JNIEnv *, jobject, jstring, jstring);

JNIEXPORT jint JNICALL Java_hn_tools_zip_Archive_listArchive2
		(JNIEnv *, jobject, jstring, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
