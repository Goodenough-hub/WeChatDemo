#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"

template <typename T>
class Singleton{ // 声明单例类
protected: // 子类可以构造父类
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete; // 不允许拷贝构造
    Singleton& operator = (const Singleton<T>& st) = delete; // 不允许拷贝赋值

    // 返回的实例不希望手动回收，用智能指针
    static std::shared_ptr<T> _instance; // 静态成员变量-所有的singleton都返回这样的一个实例
public:
    // 单例模式  https://www.cnblogs.com/xuhuajie/p/11647164.html
    static std::shared_ptr<T> GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag, [&](){ // std::once_call支持多线程情况下的某函数只执行一次。
            // 为啥不用make_shared()而用new  因为makeshared会间接调用Singleton的构造函数，而Singleton构造函数是私有的，所以会报错。
            _instance = std::shared_ptr<T>(new T);
        });

        return _instance;
    }

    void PrintAddress()
    {
        std::cout << _instance.get() << std::endl;
    }

    ~Singleton()
    {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
