/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class comulez_github_encryptlib_Encrypt4C */
#ifndef _Included_comulez_github_encryptlib_Encrypt4C
#define _Included_comulez_github_encryptlib_Encrypt4C
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     comulez_github_encryptlib_Encrypt4C
 * Method:    AES_ECB_encrypt_byte
 * Signature: ([B[B)[B
 */

JNIEXPORT jbyteArray JNICALL Java_com_example_ndktest_Encrypt4C_AES_1ECB_1encrypt_1byte
        (JNIEnv *, jobject, jbyteArray, jbyteArray);

/*
 * Class:     comulez_github_encryptlib_Encrypt4C
 * Method:    AES_ECB_decrypt_byte
 * Signature: ([B[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_example_ndktest_Encrypt4C_AES_1ECB_1decrypt_1byte
        (JNIEnv *, jobject, jbyteArray, jbyteArray);

#ifdef __cplusplus
}
#endif
#endif
