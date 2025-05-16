#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
class XThread
{
public:
    virtual void Start()
    {
        th_ = std::thread(&XThread::Main, this);
    }
    virtual void Stop()
    {
        is_exit_ = true;
        Wait();
    }
    virtual void Wait()
    {
        if(th_.joinable())
        {
            th_.join();
        }
    }
    bool is_exit() {return is_exit_;}
private:
    virtual void Main() = 0;
    std::thread th_;
    bool is_exit_ = false;
};

class TestXThread : public XThread
{
public:
    void Main() override
    {
        std::cout << "TestThread Main begin" << std::endl;
        while(!is_exit())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "." << std::flush;
        }
        std::cout << "\nTestThread Main end" << std::endl;
    }
    std::string name = "TestThread ";
};