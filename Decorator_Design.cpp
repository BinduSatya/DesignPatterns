/*
Decorator Design Pattern:
It is used to attach additional responsibilites to an object
dynamically. Decorator provides a flexible alternative to subclass for
extending functionality.


Where can be used:
1. When text will be converted to Bold, Itallic, Underline
2. Validating a form: Email Validation, SQL validation, ..., etc
*/

#include <bits/stdc++.h>
using namespace std;

class ICharacter
{
public:
    virtual string getAbilites() const = 0;
    virtual ~ICharacter() {};
};

class Mario : public ICharacter
{
public:
    string getAbilites() const override
    {
        return "Mario ";
    }
};

class CharacterDecorator : public ICharacter
{
protected:
    ICharacter *Character;

public:
    CharacterDecorator(ICharacter *c)
    {
        this->Character = c;
    }
    virtual ~CharacterDecorator()
    {
        delete Character;
    }
};

class HeightUp : public CharacterDecorator
{
public:
    HeightUp(ICharacter *ch) : CharacterDecorator(ch) {};
    string getAbilites() const override
    {
        return Character->getAbilites() + "with Height Up ";
    }
};

class GunPowerUp : public CharacterDecorator
{
public:
    GunPowerUp(ICharacter *ch) : CharacterDecorator(ch) {};
    string getAbilites() const override
    {
        return Character->getAbilites() + "with Gun Power Up ";
    }
};

class StarPower : public CharacterDecorator
{
public:
    StarPower(ICharacter *ch) : CharacterDecorator(ch) {};
    string getAbilites() const override
    {
        return Character->getAbilites() + "with Star Power Up with limited time ";
    }

    ~StarPower()
    {
        cout << "\nDestroying Star Power " << endl;
    }
};

int main()
{
    ICharacter *mario = new Mario();
    cout << "Basic Character " << mario->getAbilites() << endl;

    // Increasing Mario Height
    mario = new HeightUp(mario);
    cout << "After HeightUp:" << mario->getAbilites() << endl;

    // Giving Gun Power
    mario = new GunPowerUp(mario);
    cout << "After Gun PowerUp:" << mario->getAbilites() << endl;

    // Giving Star Power
    mario = new StarPower(mario);
    cout << "After Star PowerUp:" << mario->getAbilites() << endl;

    // losing star power;
    delete mario;
    return 0;
}