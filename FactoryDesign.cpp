#include <bits/stdc++.h>
using namespace std;

class Product
{
public:
    virtual string Operation() {};
};

class ConcreteProductA : public Product
{
public:
    string Operation() override
    {
        return "Result of ConcreteProductA";
    }
};

class ConcreteProductB : public Product
{
public:
    string Operation() override
    {
        return "Result of ConcreteProductB";
    }
};

class Creator
{
public:
    virtual Product *FactoryMethod(string prod) {};
    virtual string Factintro() {};
};

class ConcreteCreatorA : public Creator
{
public:
    string Factintro() override
    {
        return "Factory Method creates ConcreteCreator A";
    }

    Product *FactoryMethod(string prod) override
    {
        if (prod == "A")
        {
            cout << "this is A creator producing product A" << endl;
            return new ConcreteProductA();
        }
        else if (prod == "B")
        {
            cout << "this is A creator producing product B" << endl;
            return new ConcreteProductB();
        }
        else
            return nullptr;
    }
};

class ConcreteCreatorB : public Creator
{
public:
    string Factintro() override
    {
        return "Factory Method creates ConcreteCreator B";
    }

    Product *FactoryMethod(string prod) override
    {
        if (prod == "A")
        {
            cout << "this is B creator producing product A" << endl;
            return new ConcreteProductA();
        }
        else if (prod == "B")
        {
            cout << "this is B creator producing product B" << endl;
            return new ConcreteProductB();
        }
        else
            return nullptr;
    }
};

int main()
{
    Creator *creatorA = new ConcreteCreatorA();
    cout << creatorA->Factintro() << endl;

    Product *productB = creatorA->FactoryMethod("B");
    cout << productB->Operation() << endl;
    return 0;
}