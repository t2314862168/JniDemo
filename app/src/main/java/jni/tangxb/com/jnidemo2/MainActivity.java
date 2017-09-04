package jni.tangxb.com.jnidemo2;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import java.io.File;
import java.io.IOException;

import jni.tangxb.com.jnidemo2.model.Person;
import jni.tangxb.com.jnidemo2.model.Student;

/**
 * <a href="http://blog.csdn.net/markingcfx/article/details/62218307">在CMakeList使用多个cpp一起编译</a>
 */
public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("file-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
        test();
    }

    public void test() {
//        test1();
//        test2();
        test3();
        test4();
        test5();
    }

    public void test1() {
        Person person = new Person("person1", 10, 100f);
        passObject2Jni(person);
        System.out.println();
    }

    public void test2() {
        Student student = passObject2Java();
        System.out.println();
    }

    public void test3() {
        Student student = passObject2Java02();
        System.out.println();
    }

    public void test4() {
        String s = stringFromTestFile();
        System.out.println();
    }

    public void test5() {
        File directory = Environment.getExternalStorageDirectory();
        File file = new File(directory, "test.txt");
        File file2 = new File(directory, "test_2.txt");
        if (!file.exists()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        if (!file2.exists()) {
            try {
                file2.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        String absolutePath = file.getAbsolutePath();
        String absolutePath2 = file2.getAbsolutePath();
        writeStr2File(absolutePath);
        readFromFile(absolutePath);
        readFromFile2File(absolutePath, absolutePath2);
        readFromFile(absolutePath2);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     * 传递实体给JNI层，然后打印数据修改数据
     *
     * @param person
     */
    public native void passObject2Jni(Person person);

    /**
     * JNI层返回实体
     *
     * @return
     */
    public native Student passObject2Java();

    /**
     * JNI层返回实体
     *
     * @return
     */
    public native Student passObject2Java02();

    public native String stringFromTestFile();

    /**
     * 把内容写入文件里面去
     *
     * @param path
     */
    public native void writeStr2File(String path);

    /**
     * 读取文件
     *
     * @param path
     */
    public native void readFromFile(String path);

    /**
     * 把path1里面的内容赋值到path2里面去
     *
     * @param path1
     * @param path2
     */
    public native void readFromFile2File(String path1, String path2);
}
