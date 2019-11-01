package com.example.ndktest;

public interface Encrypt {
    byte[] aesEncrypt(byte[] plainText, byte[] key) throws Exception;

    byte[] aesDecrypt(byte[] cipherText, byte[] key) throws Exception;
}
