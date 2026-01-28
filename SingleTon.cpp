#include <bits/stdc++.h>
using namespace std;

class Singleton
{
private:
    static Singleton *instance;

    Singleton()
    {
        cout << "SingleTon is created\n";
    }

public:
    static Singleton *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }

    ~Singleton()
    {
        cout << "Singleton is deleted\n";
    }
};

Singleton *Singleton::instance = nullptr;

int main()
{
    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    Singleton *s3 = s3->getInstance();

    if (s1 == s2 && s3 == s2)
        cout << "same";
    else
        cout << "diff";
    return 0;
}