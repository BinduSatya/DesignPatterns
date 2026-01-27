#include <bits/stdc++.h>
using namespace std;

class Singleton
{
    Singleton()
    {
        cout << "SingleTon is created\n";
    }

public:
    static Singleton *createInstance()
    {
        if (onlyInstance != nullptr)
        {
            return new Singleton();
        }
    }
    ~Singleton()
    {
        cout << "Singleton is deleted\n";
    }
};

static Singleton *onlyInstance = nullptr;

int main()
{
    Singleton *instance = onlyInstance;
    delete instance;
    return 0;
}