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

extern "C"
JNIEXPORT jstring

JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++002";
    return env->NewStringUTF(hello.c_str());
}

/**
 * 参考链接 http://blog.csdn.net/a345017062/article/details/8068925
 */
extern "C"
JNIEXPORT void JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_passObject2Jni(JNIEnv *env, jobject instance,
                                                         jobject person) {
    LOGD("passObject2Jni()======start");
    jclass cls;
    jstring name;
    jint age;
    jfloat height;
    jboolean isStudent = false;
    const char *c_str = NULL;

    cls = env->GetObjectClass(person);
    jfieldID nameId = env->GetFieldID(cls, "mName", "Ljava/lang/String;");
    jfieldID ageId = env->GetFieldID(cls, "mAge", "I");
    jfieldID isStudentId = env->GetFieldID(cls, "isStudent", "Z");
    name = (jstring) env->GetObjectField(person, nameId);
    age = env->GetIntField(person, ageId);
    LOGD("passObject2Jni()======age==%d", age);
    isStudent = env->GetBooleanField(person, isStudentId);
    LOGD("passObject2Jni()======isStudent==%d", isStudent);
    c_str = env->GetStringUTFChars(name, false);
    LOGD("passObject2Jni()======name==%s", c_str);
    env->SetObjectField(person, nameId, env->NewStringUTF("person from jni"));
    env->SetIntField(person, ageId, 20);
    env->SetBooleanField(person, isStudentId, false);

    const char *c_str_2 = NULL;
    jmethodID toStringMethodID = env->GetMethodID(cls, "toString", "()Ljava/lang/String;");
    jmethodID ageMethodID = env->GetMethodID(cls, "getmAge", "()I");
    jint getAge = env->CallIntMethod(person, ageMethodID);
    jstring toString = (jstring) env->CallObjectMethod(person, toStringMethodID);
    c_str_2 = env->GetStringUTFChars(toString, false);
    LOGD("passObject2Jni()======getAge==%d", getAge);
    LOGD("passObject2Jni()======toString==%s", c_str_2);

    env->DeleteLocalRef(cls);
    env->ReleaseStringUTFChars(name, c_str);
    env->ReleaseStringUTFChars(toString, c_str_2);
    LOGD("passObject2Jni()======end");
}

/**
 * http://blog.csdn.net/lintax/article/details/51759270
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_passObject2Java(JNIEnv *env, jobject instance) {
    jobject student = NULL;
    jclass student_cls = env->FindClass("jni/tangxb/com/jnidemo2/model/Student");
    jmethodID student_mtd = env->GetMethodID(student_cls, "<init>", "(ILjava/lang/String;)V");
    jstring jstr = env->NewStringUTF("[Jay]");
    student = env->NewObject(student_cls, student_mtd, 10, jstr);
    env->DeleteLocalRef(jstr);
    return student;
}

typedef struct {
    char name[255];
    int number;
} Student;

/**
 * http://blog.csdn.net/lintax/article/details/51759270
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_jni_tangxb_com_jnidemo2_MainActivity_passObject2Java02(JNIEnv *env, jobject instance) {
    jobject student = NULL;
    Student student1;
    strcpy(student1.name, "Fuck You");
    student1.number = 250;
    jclass student_cls = env->FindClass("jni/tangxb/com/jnidemo2/model/Student");
    jmethodID student_mtd = env->GetMethodID(student_cls, "<init>", "(ILjava/lang/String;)V");
    jstring jstr = env->NewStringUTF(student1.name);
    student = env->NewObject(student_cls, student_mtd, student1.number, jstr);
    env->DeleteLocalRef(jstr);
    return student;
}