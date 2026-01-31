/*
Strategy Design:
It defines a family of algorithms, put them into separate classes so that
they can be changed at runtim.

1. Encapsulate what varies and keep it separate from what remains same.
2. Solution to inheritance is not more inheritance, its composition
3. Composition should be favoured over inheritance.


Use Cases:
1. Payment Methods: User can dynamically select which payment method he wants
*/

#include <bits/stdc++.h>
using namespace std;

class WalkableRobot
{
public:
    virtual void walk() = 0;
    ~WalkableRobot() {};
};

class NormalWalk : public WalkableRobot
{
public:
    void walk() override
    {
        cout << "Walking Normally..." << endl;
    }
};

class NoWalk : public WalkableRobot
{
public:
    void walk() override
    {
        cout << "Cannot Walk..." << endl;
    }
};

class TalkableRobot
{
public:
    virtual void talk() = 0;
    ~TalkableRobot() {};
};

class NormalTalk : public TalkableRobot
{
public:
    void talk() override
    {
        cout << "Talking Normally..." << endl;
    }
};

class NoTalk : public TalkableRobot
{
public:
    void talk() override
    {
        cout << "Cannot Talk..." << endl;
    }
};

class FlyableRobot
{
public:
    virtual void fly() = 0;
    ~FlyableRobot() {};
};

class NormalFly : public FlyableRobot
{
public:
    void fly() override
    {
        cout << "Talking Normally..." << endl;
    }
};

class NoFly : public FlyableRobot
{
public:
    void fly() override
    {
        cout << "Cannot Talk..." << endl;
    }
};

class Robot
{
protected:
    WalkableRobot *walkBehaviour;
    TalkableRobot *talkBehaviour;
    FlyableRobot *flyBehaviour;

public:
    Robot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f)
    {
        walkBehaviour = w;
        talkBehaviour = t;
        flyBehaviour = f;
    }

    void walk()
    {
        walkBehaviour->walk();
    }

    void talk()
    {
        talkBehaviour->talk();
    }

    void fly()
    {
        flyBehaviour->fly();
    }

    virtual void projection() = 0;
};

class CompanionRobot : public Robot
{
public:
    CompanionRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f) : Robot(w, t, f) {}

    void projection() override
    {
        cout << "Displaying Companion Robot" << endl;
    }
};

class WorkRobot : public Robot
{
public:
    WorkRobot(WalkableRobot *w, TalkableRobot *t, FlyableRobot *f) : Robot(w, t, f) {}

    void projection() override
    {
        cout << "Displaying Worker Robot" << endl;
    }
};

int main()
{

    Robot *worker = new WorkRobot(new NormalWalk(), new NoTalk(), new NormalFly());
    worker->projection();
}