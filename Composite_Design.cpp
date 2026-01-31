/*
Composite Design:
Composite Pattern composes object into tree like structure representing a
part-whole hierrarchy. It lets client treats individual objects and
composition of object uniformly.

1. It is used to design a File System.
2.
*/

#include <bits/stdc++.h>
using namespace std;

class FileSystemItem
{
public:
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual int getSize() = 0;
    virtual string getName() = 0;
    virtual bool isFolder() = 0;
    virtual FileSystemItem *cd(string name) = 0;
    virtual ~FileSystemItem() {};
};

class File : public FileSystemItem
{
    string name;
    int size;

public:
    File(string n, int s)
    {
        this->name = n;
        this->size = s;
    }

    void ls(int indent = 0) override
    {
        cout << string(indent, ' ') << name << endl;
    }

    // Since it is file, no OpenAll will be existing
    void openAll(int indent = 0) override
    {
        cout << string(indent, ' ') << name << endl;
    }

    int getSize() override
    {
        return size;
    }

    FileSystemItem *cd(string name) override
    {
        return nullptr;
    }

    string getName() override
    {
        return name;
    }

    bool isFolder() override
    {
        return false;
    }
};

class Folder : public FileSystemItem
{
    string name;
    vector<FileSystemItem *> children;

public:
    Folder(string n)
    {
        this->name = n;
    }

    ~Folder()
    {
        for (FileSystemItem *child : children)
        {
            delete child;
        }
    }

    void add(FileSystemItem *item)
    {
        children.push_back(item);
    }

    void ls(int indent = 0) override
    {
        for (auto &it : children)
        {
            if (it->isFolder())
            {
                cout << string(indent, ' ') << "+ " << it->getName() << endl;
            }
            else
            {
                cout << string(indent, ' ') << it->getName() << endl;
            }
        }
    }

    // Since it is Folder, OpenAll will be existing
    void openAll(int indent = 0) override
    {
        cout << string(indent, ' ') << "+ " << name << endl;
        for (auto &it : children)
        {
            it->openAll(indent + 4);
        }
    }

    int getSize() override
    {
        int total = 0;
        for (auto &it : children)
        {
            total += it->getSize();
        }
        return total;
    }

    FileSystemItem *cd(string name) override
    {

        for (auto &it : children)
        {
            if (it->isFolder() && it->getName() == name)
            {
                return it;
            }
        }
        return nullptr;
    }

    string getName() override
    {
        return name;
    }

    bool isFolder() override
    {
        return true;
    }
};

int main()
{
    // Initialising root and adding files and Folders
    Folder *root = new Folder("root");
    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 3));
    root->add(new File("file3.txt", 4));

    Folder *docs = new Folder("docs");
    docs->add(new File("resume.docx", 10));
    docs->add(new File("resume2.pdf", 12));
    root->add(docs);

    Folder *images = new Folder("images");
    images->add(new File("image.jpg", 1));
    images->add(new File("image2.jpg", 2));
    images->add(new File("image3.jpg", 5));
    docs->add(images);

    // Checking the methods
    // root->ls();
    // root->openAll();

    // cout << docs->getName() << endl;
    // cout << docs->getSize() << endl;

    FileSystemItem *item = root->cd("docs");
    if (item == nullptr)
    {
        cout << "there is no folder like that" << endl;
    }
    else
    {
        cout << item->getSize() << endl;
    }
}