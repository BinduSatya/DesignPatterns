/*
Decorator Design Pattern:
It is used to attach additional responsibilites to an object
dynamically. Decorator provides a flexible alternative to subclass for
extending functionality.

- With this design pattern, we can only add decorators, but can't remove them.
Where can be used:
1. When text will be converted to Bold, Itallic, Underline
2. Validating a form: Email Validation, SQL validation, ..., etc
*/

#include <bits/stdc++.h>
using namespace std;

class Coffee
{
public:
    virtual string getDescription() = 0;
    virtual double getCost() = 0;
    virtual ~Coffee() {};
};

class Espresso : public Coffee
{

public:
    string getDescription()
    {
        return "Espresso";
    }
    double getCost() override
    {
        return 150.00;
    }
};

class CoffeeDecorator : public Coffee
{
protected:
    Coffee *coffee;

public:
    CoffeeDecorator(Coffee *c) : coffee(c) {};
    virtual ~CoffeeDecorator()
    {
        delete coffee;
    }
};

class AddMilk : public CoffeeDecorator
{
public:
    AddMilk(Coffee *ch) : CoffeeDecorator(ch) {};
    string getDescription() override
    {
        return coffee->getDescription() + " with Milk";
    }

    double getCost() override
    {
        return coffee->getCost() + 49.99;
    }
};

class AddSugar : public CoffeeDecorator
{
public:
    AddSugar(Coffee *ch) : CoffeeDecorator(ch) {};
    string getDescription() override
    {
        return coffee->getDescription() + " with Sugar";
    }

    double getCost() override
    {
        return coffee->getCost() + 19.99;
    }
};

class AddFoam : public CoffeeDecorator
{
public:
    AddFoam(Coffee *ch) : CoffeeDecorator(ch) {};
    string getDescription() override
    {
        return coffee->getDescription() + " with Foam";
    }

    double getCost() override
    {
        return coffee->getCost() + 4.99;
    }
};

int main()
{
    Coffee *espresso = new Espresso();
    cout << espresso->getDescription() << endl;
    cout << espresso->getCost() << endl;

    // Adding Milk
    espresso = new AddMilk(espresso);
    cout << espresso->getDescription() << endl;
    cout << espresso->getCost() << endl;

    // Adding Sugar
    espresso = new AddSugar(espresso);
    cout << espresso->getDescription() << endl;
    cout << espresso->getCost() << endl;

    // Adding Foam
    espresso = new AddFoam(espresso);
    cout << espresso->getDescription() << endl;
    cout << espresso->getCost() << endl;
    delete espresso;
    return 0;
}