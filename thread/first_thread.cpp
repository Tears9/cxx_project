#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "XThread.hpp"

using namespace std;


class MyThread
{
public:
    // 入口线程函数
    void Main()
    {
        cout << "MyThread Main " << name << " : " << age << endl;
        return ;
    }
    string name = "";
    int age = 100;

};


class Para
{
public:
    Para(const char* str) : name(str){cout << "Create Para" <<endl;}
    Para(const Para& para): name(para.name){cout << "Copy Para" <<endl;}
    ~Para() {cout << "Destroy Para" <<endl;}
    const string& GetName() const {return name;}
private:
    string name;
};

class TestLambda
{
public:
    void Run()
    {
        // 捕获 this 指针以使用成员变量
        thread th([this]() {cout << "name = " << name <<endl;});
        this_thread::sleep_for(chrono::milliseconds(10));
        th.join();
    }
    string name = "test lambda";
};

void ThreadMainRef(int num, Para& para)
{
    cout << "begin sub thread main "<< this_thread::get_id() << endl;
    for(int i = 0; i < num; ++i)
    {
        cout << para.GetName() << i <<endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return ;
}

void ThreadMain(int num, string str)
{
    cout << "begin sub thread main "<< this_thread::get_id() << endl;
    for(int i = 0; i < num; ++i)
    {
        cout << str << i <<endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    return ;
}

int main(int argc, char* argv[])
{
    cout << "main thread ID " << this_thread::get_id()<<endl;

/*
    {
        // 引用传递参数
        Para p("Ref thread ");
        thread th1(ThreadMainRef, 5, ref(p)); // 一定要用 ref 去告诉模板使用引用
        this_thread::sleep_for(chrono::milliseconds(10)); 

        th1.join();
        getchar();
    }
*/
/*
    {
        MyThread myth;
        myth.name = "Test name 001";
        myth.age = 55;
        thread th2(&MyThread::Main, &myth);
        this_thread::sleep_for(chrono::milliseconds(10)); 

        th2.join();
        getchar();
    }
*/
/*
    {
        TestXThread testth;
        testth.Start();
        this_thread::sleep_for(chrono::seconds(3));
        testth.Stop();
        getchar();
    }
*/
/*
    {
        thread th3([](int i)
                    {
                      cout << "test lambda " << i << endl;  
                    }
                ,10);
        th3.join();
        getchar();
    }
*/
    {
        TestLambda tl;
        tl.Run();
        getchar();
    }
    thread th(ThreadMain, 5 , "in thread "); // 确保 thread 对象的生命期
    // th.detach(); // 线程分离，主线程退出后子线程不一定退出
    this_thread::sleep_for(chrono::milliseconds(10)); // 子线程先行

    cout<<"wait sub thread " << endl;
    th.join();
    cout<<"end wait sub thread " << endl;
    
    return 0;
}




