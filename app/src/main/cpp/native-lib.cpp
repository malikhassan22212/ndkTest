#include <jni.h>
#include <string>
#include "log.h"
#include "comulez_github_encryptlib_Encrypt4C.h"
#include <stdio.h>
#include <stdint.h>
#define CBC 1
#define ECB 1
static void test_encrypt_ecb(void);

jbyteArray as_byte_array(JNIEnv *env, unsigned char *buf, int len);

unsigned char *as_unsigned_char_array(JNIEnv *env, jbyteArray array);
extern "C" {
#include "aes.h"
}
/**
 * 加密
 * @param env
 * @param instance
 * @param originByte
 * @param keyByte
 * @return
 */
JNIEXPORT jbyteArray JNICALL Java_com_example_ndktest_Encrypt4C_AES_1ECB_1encrypt_1byte
        (JNIEnv *env, jobject instance, jbyteArray originByte, jbyteArray keyByte) {
    jsize alen = env->GetArrayLength(originByte); //获取长度
    unsigned char *originChar = as_unsigned_char_array(env, originByte);
    unsigned char *keyByteChar = as_unsigned_char_array(env, keyByte);
    //originChar 正确；
    int len;
    if (alen % 16 == 0) {
        int xxx = alen / 16;
        len = (xxx) * 16;
    } else {
        int xxx = alen / 16;
        len = (xxx + 1) * 16;
    }
    int ss = sizeof(originChar);
    uint8_t buffer[len];
    AES_ECB_encrypt(originChar, keyByteChar, buffer, len);
    return as_byte_array(env, buffer, len);
}

/**
 * 解密
 * @param env
 * @param instance
 * @param originByte
 * @param keyByte
 * @return
 */
JNIEXPORT jbyteArray JNICALL Java_com_example_ndktest_Encrypt4C_AES_1ECB_1decrypt_1byte
        (JNIEnv *env, jobject instance, jbyteArray originByte, jbyteArray keyByte) {
    jsize len = env->GetArrayLength(originByte); //获取长度
    unsigned char *originChar = as_unsigned_char_array(env, originByte);
    unsigned char *keyByteChar = as_unsigned_char_array(env, keyByte);
    uint8_t buffer[len];
    AES_ECB_decrypt(originChar, keyByteChar, buffer, len);
    int realLen = 0;
    for (int i = 0; i < len; i++) {
        if (buffer[i] == '\0') {
            break;
        }
        realLen++;
    }
    return as_byte_array(env, buffer, realLen);
}

/**
 * unsigned char 转化为 jbyteArray 返回
 * @param env
 * @param buf
 * @param len
 * @return
 */
jbyteArray as_byte_array(JNIEnv *env, unsigned char *buf, int len) {
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(buf));
    return array;
}

/**
 * jbyteArray 转化为 unsigned char 返回
 * @param env
 * @param array
 * @return
 */
unsigned char *as_unsigned_char_array(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength(array);
    unsigned char *buf = new unsigned char[len+1];
    env->GetByteArrayRegion(array, 0, len, reinterpret_cast<jbyte *>(buf));
    buf[len]='\0';
    return buf;
}


static void test_encrypt_ecb(void) {
#ifdef AES128
    uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88,
                     0x09,
                     0xcf, 0x4f, 0x3c};
    uint8_t out[] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3,
                     0x24,
                     0x66, 0xef, 0x97};
#elif defined(AES192)
    uint8_t key[] = { 0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5,
                    0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b};
  uint8_t out[] = { 0xbd, 0x33, 0x4f, 0x1d, 0x6e, 0x45, 0xf2, 0x5f, 0xf7, 0x12, 0xa2, 0x14, 0x57, 0x1f, 0xa5, 0xcc };
#elif defined(AES256)
    uint8_t key[] = { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                      0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };
    uint8_t out[] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };
#endif

    uint8_t in[] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11,
                    0x73,
                    0x93, 0x17, 0x2a};
    uint8_t buffer[16];

    AES_ECB_encrypt(in, key, buffer, 16);

    printf("ECB aesEncrypt:");

    if (0 == memcmp((char *) out, (char *) buffer, 16)) {
        printf("SUCCESS!\n");
        LOGI("SUCCESS!");
    } else {
        printf("FAILURE!\n");
        LOGE("FAILURE!\n");
    }
}