package jni.tangxb.com.jnidemo2.model;

/**
 * Created by Taxngb on 2017/9/1.
 */

public class Person {
    private String mName;
    private int mAge;
    private float mHeight;
    private boolean isStudent;
    public Person() {
    }

    public Person(String mName, int mAge, float mHeight) {
        this.mName = mName;
        this.mAge = mAge;
        this.mHeight = mHeight;
        isStudent = true;
    }

    public boolean isStudent() {
        return isStudent;
    }

    public void setStudent(boolean student) {
        isStudent = student;
    }

    public String getmName() {
        return mName;
    }

    public void setmName(String mName) {
        this.mName = mName;
    }

    public int getmAge() {
        return mAge;
    }

    public void setmAge(int mAge) {
        this.mAge = mAge;
    }

    public float getmHeight() {
        return mHeight;
    }

    public void setmHeight(float mHeight) {
        this.mHeight = mHeight;
    }

    @Override
    public String toString() {
        return "Person{" +
                "mName='" + mName + '\'' +
                ", mAge=" + mAge +
                ", mHeight=" + mHeight +
                ", isStudent=" + isStudent +
                '}';
    }
}