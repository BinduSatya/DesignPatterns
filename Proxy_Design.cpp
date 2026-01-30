/*
Proxy Design:
Proxy Object is used to act as a placeholder or surrogate for another
object to control access to it.

There are different type of proxies present:
Virtual, Protection, Remote
*/

#include <bits/stdc++.h>
using namespace std;

class IImage
{
public:
    virtual void getData() = 0;
    ~IImage() = default;
};

class RealImage : public IImage
{
public:
    string name;
    float size;
    long date;

    RealImage(string name,
              float size,
              long date)
    {
        this->date = date;
        this->name = name;
        this->size = size;

        cout << "Real Image is loading from disk..." << endl;
    }

    void getData()
    {
        cout << "This is a some costly operation" << endl;
        cout << "this image is " << name << " of size " << size << " taken on " << date << endl;
    }
};

class ProxyImage : public IImage
{
public:
    IImage *file;
    string name;
    float size;
    long date;

    ProxyImage(string name,
               float size,
               long date)
    {
        this->date = date;
        this->name = name;
        this->size = size;
        this->file = nullptr;
        cout << "Proxy Image is loading from disk..." << endl;
    }

    void getData()
    {
        cout << "Calling Proxy getData func" << endl;
        if (!file)
        {
            cout << "File not yet created" << endl;
            file = new RealImage(name, size, date);
        }
        file->getData();
    }
};

int main()
{
    IImage *proxy = new ProxyImage("bindu", 0.3, 2234);
    proxy->getData();
}