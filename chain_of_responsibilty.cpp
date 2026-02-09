/*
In ATM centre, there will be different type of denominations (100, 500, 2000 notes)

Chain of Responsisbility:
It allows to pass a request to a object (handler) that has 
chain of handler attached to it. Each handler decides
whether to process the request or pass to the next handler that may process
the user request
*/

#include <bits/stdc++.h>
using namespace std;

class MoneyHandler
{
protected:
    MoneyHandler *nextHandler;

public:
    MoneyHandler()
    {
        this->nextHandler = nullptr;
    }

    void setNextHandler(MoneyHandler *next)
    {
        nextHandler = next;
    }

    virtual void dispense(int amount) = 0;
};

class ThousandMoneyHandler : public MoneyHandler
{
private:
    int notes;

public:
    ThousandMoneyHandler(int notes)
    {
        this->notes = notes;
    }

    void dispense(int amount) override
    {
        int notesNeeded = amount / notes;

        if (notesNeeded <= notes)
        {
            notes -= notesNeeded;
        }
        else
        {
            notesNeeded = notes;
            notes = 0;
        }

        if (notesNeeded > 0)
        {
            cout << "Dispensing " << notesNeeded << "X 1000 rup." << endl;
        }
        int remainingAmount = amount - (notesNeeded * 1000);
        if (remainingAmount > 0)
        {
            if (nextHandler != nullptr)
            {
                nextHandler->dispense(remainingAmount);
            }
            else
            {
                cout << "Remainig amount of " << remainingAmount << " cann't be fullfilled" << endl;
            }
        }
    }
};

class FiveHundredMoneyHandler : public MoneyHandler
{
private:
    int notes;

public:
    FiveHundredMoneyHandler(int notes)
    {
        this->notes = notes;
    }

    void dispense(int amount) override
    {
        int notesNeeded = amount / notes;

        if (notesNeeded <= notes)
        {
            notes -= notesNeeded;
        }
        else
        {
            notesNeeded = notes;
            notes = 0;
        }

        if (notesNeeded > 0)
        {
            cout << "Dispensing " << notesNeeded << "X 500 rup." << endl;
        }
        int remainingAmount = amount - (notesNeeded * 500);
        if (remainingAmount > 0)
        {
            if (nextHandler != nullptr)
            {
                nextHandler->dispense(remainingAmount);
            }
            else
            {
                cout << "Remainig amount of " << remainingAmount << " cann't be fullfilled" << endl;
            }
        }
    }
};

class TwoHundredMoneyHandler : public MoneyHandler
{
private:
    int notes;

public:
    TwoHundredMoneyHandler(int notes)
    {
        this->notes = notes;
    }

    void dispense(int amount) override
    {
        int notesNeeded = amount / notes;

        if (notesNeeded <= notes)
        {
            notes -= notesNeeded;
        }
        else
        {
            notesNeeded = notes;
            notes = 0;
        }

        if (notesNeeded > 0)
        {
            cout << "Dispensing " << notesNeeded << "X 200 rup." << endl;
        }
        int remainingAmount = amount - (notesNeeded * 200);
        if (remainingAmount > 0)
        {
            if (nextHandler != nullptr)
            {
                nextHandler->dispense(remainingAmount);
            }
            else
            {
                cout << "Remainig amount of " << remainingAmount << " cann't be fullfilled" << endl;
            }
        }
    }
};

class HundredMoneyHandler : public MoneyHandler
{
private:
    int notes;

public:
    HundredMoneyHandler(int notes)
    {
        this->notes = notes;
    }

    void dispense(int amount) override
    {
        int notesNeeded = amount / notes;

        if (notesNeeded <= notes)
        {
            notes -= notesNeeded;
        }
        else
        {
            notesNeeded = notes;
            notes = 0;
        }

        if (notesNeeded > 0)
        {
            cout << "Dispensing " << notesNeeded << "X 100 rup." << endl;
        }
        int remainingAmount = amount - (notesNeeded * 100);
        if (remainingAmount > 0)
        {
            if (nextHandler != nullptr)
            {
                nextHandler->dispense(remainingAmount);
            }
            else
            {
                cout << "Remainig amount of " << remainingAmount << " cann't be fullfilled" << endl;
            }
        }
    }
};

int main()
{
    MoneyHandler *thousandHandler = new ThousandMoneyHandler(3);
    MoneyHandler *fiveHundredHandler = new FiveHundredMoneyHandler(2);
    MoneyHandler *twoHundredHandler = new TwoHundredMoneyHandler(13);
    MoneyHandler *hundredHandler = new HundredMoneyHandler(19);

    thousandHandler->setNextHandler(fiveHundredHandler);
    fiveHundredHandler->setNextHandler(twoHundredHandler);
    twoHundredHandler->setNextHandler(hundredHandler);

    thousandHandler->dispense(300);
}