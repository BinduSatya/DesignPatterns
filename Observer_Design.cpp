/*
Whenever there is a change in the state of the object,
then other objects need to know that the object is changed.

Solution:
When a observer subscriber subscribed to observable,
then the observable appends the observer into a list,
and when there is change in the state of the observer then
it will send the new changes to all those subscribers(observables)
*/

#include <bits/stdc++.h>
using namespace std;

class ISubscriber
{
public:
    virtual void update() = 0;
    virtual ~ISubscriber() {};
};

class IChannel
{
public:
    virtual void subscribe(ISubscriber *subscriber) = 0;
    virtual void unsubscribe(ISubscriber *subscriber) = 0;
    virtual void notify() = 0;
    virtual ~IChannel() {};
};

class Channel : public IChannel
{
private:
    vector<ISubscriber *> subscribers;
    string latestVideo;

public:
    string name;
    Channel(string name)
    {
        this->name = name;
    }

    void subscribe(ISubscriber *subscriber) override
    {
        cout << "\nHurray, new subscriber subscribed";
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it == subscribers.end())
        {
            subscribers.push_back(subscriber);
        }
    }

    void unsubscribe(ISubscriber *subscriber) override
    {
        cout << "\nA subscriber unscribed";
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if (it != subscribers.end())
        {
            subscribers.erase(it);
        }
    }

    void notify() override
    {
        for (auto &it : subscribers)
        {
            it->update();
        }
    }

    void uploadVideo(string title)
    {
        latestVideo = title;
        cout << "\nNew video '" << title << "' is released.";
        notify();
    }

    string getVideoData()
    {
        return "\n" + latestVideo + "\n";
    }
};

class Subscriber : public ISubscriber
{
private:
    string name;
    Channel *channel = nullptr;

public:
    Subscriber(string name)
    {
        this->name = name;
    }

    void subscribe(Channel *channel)
    {
        this->channel = channel;
        channel->subscribe(this);
    }

    void unsubscribe(Channel *channel)
    {
        this->channel = channel;
        channel->unsubscribe(this);
    }

    void update() override
    {
        if (this->channel != nullptr)
        {
            cout << "\nHey " + this->name + " Getting latest video from the channel " + this->channel->name + " is " + this->channel->getVideoData();
        }
        else
        {
            cout << "\nYou are not subscribed to any channel\n";
        }
    }
};

int main()
{
    Channel *channel = new Channel("Bindu Satya Creates");
    Subscriber *bindu = new Subscriber("bindu");
    Subscriber *satya = new Subscriber("satya");
    bindu->subscribe(channel);
    channel->uploadVideo("How to get over procastination");
    satya->subscribe(channel);
    channel->uploadVideo("I am too tired now");
    bindu->unsubscribe(channel);
    channel->uploadVideo("I am back");
    return 0;
};