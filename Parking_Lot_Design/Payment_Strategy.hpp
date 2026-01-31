#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy
{
public:
    virtual void processPayment(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy
{
public:
    void processPayment(double amount)
    {
        cout << "Processing Credit card payment of amount ₹" << amount << endl;
    }
};

class UPIPayment : public PaymentStrategy
{
public:
    void processPayment(double amount) override
    {
        cout << "Processing UPI payment of amount ₹" << amount << endl;
    }
};

class EMIPayment : public PaymentStrategy
{
public:
    void processPayment(double amount) override
    {
        cout << "Processing EMI payment of amount ₹" << amount << endl;
    }
};

class Payment
{
private:
    double amount;
    PaymentStrategy *paymentStrat;

public:
    Payment(double amount, PaymentStrategy *payStrat)
    {
        this->amount = amount;
        this->paymentStrat = payStrat;
    }

    void processPayment()
    {
        if (amount > 0)
        { 
            paymentStrat->processPayment(amount);
        }
        else
        {
            cout << "Invalid Payment amount" << endl;
        }
        return;
    }
};