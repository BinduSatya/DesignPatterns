/*
A Cache System is designed to efficiently store and retrieve data while
managing limited memory resource.

It should manage
1. Insertion
2. Retrieval
3. Eviction of data based on specific policies (LRU)
4. Each Entry will be having a key & value pairs
5. User should: get, put & remove the data.
6. Concurrent access of data should be handled (Thread Safe).
7. No locking during multiple reads, but locking during writes for consistency in data.

- Shared Lock  = Reads
- Exclusive Lock = Writes & Evictions
- 


--------------------------------------------------------------

User should
1. Access data,
2. create/update data

There are multiple ways to write to Cache & db
1. Write back policy
2. Write around policy
3. Write through policy

Here we are doing to implement write through policy for better consistency

For better consistency we are making each transaction of a key as single threaded:
    We are hashing the values of a key and based on the value of the hash, thread will
    be assigned to that key, so that there won't be any parallelism for the operation of
    that particular key.

The cache system should be extensible to other strategies and custom write policies.

Key Components:
1. Storage Interface:
    1.1. CacheStorage (string, string):
        Operations: put, get, remove, containstrings, size, getCapacity
    1.2. DatabaseStorage (string, string):
        Operations: write, read, delete

Challenges:
1. Ensuring all operations for a key leads to thread
2. Implementing LRU algorithm in thread safe manner
3. Managing synchronization with cache & db
4. Designing Hash Mechanism

Strategies:
1. Strategy Pattern for eviction and write policy


*/

#include <bits/stdc++.h>
using namespace std;

// class string
// {
//     string key;

// public:
//     string getstring()
//     {
//         return key;
//     }

//     void setstring(string key)
//     {
//         this->key = key;
//     }

//     virtual ~string() = default;
// };

// class string
// {
//     string value;

// public:
//     string getstring()
//     {
//         return value;
//     }

//     void setstring(string value)
//     {
//         this->value = value;
//     }
//     virtual ~string() = default;
// };

class CacheStorage
{
public:
    virtual void put(string k, string v) = 0;
    virtual string get(string k) = 0;
    virtual void remove(string k) = 0;
    virtual bool containsString(string k) = 0;
    virtual int size() = 0;
    virtual int getCapacity() = 0;

    virtual ~CacheStorage() = default;
};

class DBStorage
{
public:
    virtual void write(string key, string value) = 0;
    virtual string read(string key) = 0;
    virtual void del(string key) = 0;
    virtual ~DBStorage() = default;
};

class InMemoryCacheStorage : public CacheStorage
{
    unordered_map<string, string> cache;
    int capacity;

public:
    InMemoryCacheStorage(int cap)
    {
        capacity = cap;
    }

    void put(string key, string val)
    {
        cache[key] = val;
    }

    string get(string key) override
    {
        if (cache.find(key) != cache.end())
        {
            return cache[key];
        }
        else
        {
            cout << "No key present" << endl;
            return "";
        }
    }

    void remove(string k) override
    {
        if (cache.find(k) != cache.end())
        {
            cout << "Removed key :'" << k << "' successfully" << endl;
            cache.erase(k);
        }
        else
        {
            cout << "No key is present : " << k << endl;
            return;
        }
    }

    bool containsString(string k) override
    {
        return cache.find(k) != cache.end();
    }

    int size() override
    {
        return cache.size();
    }

    int getCapacity() override
    {
        return capacity;
    }
};

class SimpleDBStorage : public DBStorage
{
    unordered_map<string, string> storage;

public:
    void write(string key, string value) override
    {
        storage[key] = value;
    }

    string read(string key) override
    {
        if (storage.find(key) != storage.end())
        {
            return storage[key];
        }
        return "";
    }

    void del(string key) override
    {
        if (storage.find(key) != storage.end())
        {
            storage.erase(key);
        }
    }
};

class WritePolicy
{
public:
    virtual void write(string key, string val, CacheStorage *cache, DBStorage *db) = 0;
    virtual ~WritePolicy() = default;
};

class EvictionAlgorithm
{
public:
    virtual void keyAccessed(string key) = 0;
    virtual string evictNode() = 0;
    virtual ~EvictionAlgorithm() = default;
};

class WriteThroughPolicy : public WritePolicy
{
public:
    void write(string key, string val, CacheStorage *cache, DBStorage *db) override
    {
        cache->put(key, val);
        db->write(key, val);
    }
};

class Node
{
public:
    string key;
    Node *prev;
    Node *next;

    Node(string k)
    {
        key = k;
        prev = next = nullptr;
    }
};

class LRUEvictionAlgorithm : public EvictionAlgorithm
{
public:
    unordered_map<string, Node *> mp;
    Node *head;
    Node *tail;

    LRUEvictionAlgorithm()
    {
        head = new Node("");
        tail = new Node("");
        head->next = tail;
        tail->prev = head;
    }

    void remove(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    string evictNode()
    {
        if (tail->prev == head)
        {
            return "";
        }
        Node *node = tail->prev;
        remove(node);
        mp.erase(node->key);
        string key = node->key;
        delete node;
        return key;
    }

    void putInFront(Node *node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void keyAccessed(string key)
    {
        if (mp.find(key) == mp.end())
        {
            Node *node = new Node(key);
            putInFront(node);
            mp[key] = node;
        }
        else
        {
            Node *node = mp[key];
            remove(node);
            putInFront(node);
        }
    }

    ~LRUEvictionAlgorithm()
    {
        Node *curr = head;
        while (curr)
        {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

class Cache
{
    CacheStorage *storage;
    EvictionAlgorithm *evictionAlgo;
    WritePolicy *writePolicy;
    DBStorage *db;

public:
    Cache(CacheStorage *s,
          EvictionAlgorithm *e,
          WritePolicy *w,
          DBStorage *d)
        : storage(s), evictionAlgo(e), writePolicy(w), db(d) {}

    void put(string key, string value)
    {
        if (!storage->containsString(key) &&
            storage->size() >= storage->getCapacity())
        {
            string evicted = evictionAlgo->evictNode();
            if (!evicted.empty())
            {
                storage->remove(evicted);
            }
        }

        writePolicy->write(key, value, storage, db);
        evictionAlgo->keyAccessed(key);
    }

    string get(string key)
    {
        if (!storage->containsString(key))
        {
            string val = db->read(key);
            if (val == "")
            {
                cout << "No such key is present in db" << endl;
                return "";
            }
            put(key, val);
            return val;
        }
        evictionAlgo->keyAccessed(key);
        return storage->get(key);
    }
};
