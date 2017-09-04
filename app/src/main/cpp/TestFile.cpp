//
// Created by Administrator on 2017/9/1.
//
#include <jni.h>
#include <string>
#include <android/log.h>

#define TAG "LogDebug"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
using namespace std;
extern "C"
JNIEXPORT jstring JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_stringFromTestFile(JNIEnv *env, jobject instance) {
    string hello = "我是你的大爷!!!";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_writeStr2File(JNIEnv *env, jobject instance,
                                                        jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    FILE *fd;
    fd = fopen(path, "w+");
    const char *char_2 = "When a Unicode stream-I/O function operates in text mode (the default), the source or destination stream is assumed to be a sequence of multibyte characters. Therefore, the Unicode stream-input functions convert multibyte characters to wide characters.";
    int sLen = strlen(char_2);
    int len = fwrite(char_2, sLen, 1, fd);
    fclose(fd);

    LOGD("writeStr2File======write content==%d", len);

    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_readFromFile(JNIEnv *env, jobject instance,
                                                       jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    FILE *pFile = fopen(path, "rb");
    fseek(pFile, 0, SEEK_END);
    int len = ftell(pFile);
    char *szBuf = new char[len];
    memset(szBuf, 0, len);
    fseek(pFile, 0, SEEK_SET);
    int iRead = fread(szBuf, len, 1, pFile);
    LOGD("readFromFile======read content==%s", szBuf);
    delete (szBuf);
    fclose(pFile);
    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_readFromFile2File(JNIEnv *env, jobject instance,
                                                            jstring path1_, jstring path2_) {
    const char *path1 = env->GetStringUTFChars(path1_, 0);
    const char *path2 = env->GetStringUTFChars(path2_, 0);
    FILE *pFile = fopen(path1, "rb");
    FILE *pFile2 = fopen(path2, "w+");
    fseek(pFile, 0, SEEK_END);
    int len = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    int minLen = 100;
    int bufferSize = len > minLen ? minLen : len;
    char *szBuf = new char[bufferSize];
    int totalCount = len;
    int readCount = 0;
    while (readCount < totalCount) {
        memset(szBuf, 0, bufferSize);
        int needCount = totalCount - readCount;
        if (needCount > bufferSize) {
            needCount = bufferSize;
        }
        // 读取文件
        fread(szBuf, needCount, 1, pFile);
        // 写入文件
        fwrite(szBuf, needCount, 1, pFile2);
        readCount += needCount;
    }
    delete (szBuf);
    fclose(pFile2);
    fclose(pFile);
    env->ReleaseStringUTFChars(path1_, path1);
    env->ReleaseStringUTFChars(path2_, path2);
}