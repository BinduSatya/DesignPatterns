#pragma once
#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy
{
public:
    virtual ~PaymentStrategy() = default;
    virtual void process(double amount) = 0;
};

class CreditCardPayment : public PaymentStrategy
{
public:
    CreditCardPayment()
    {
        cout << "Credit Card Payment Initiated" << endl;
    }

    void process(double amount) override
    {
        cout << "Processing Credit card payment of amount Rup. " << ceil(amount) << endl;
    }
};

class UPIPayment : public PaymentStrategy
{
public:
    UPIPayment()
    {
        cout << "Credit Card Payment Initiated" << endl;
    }

    void process(double amount) override
    {
        cout << "Processing UPI payment of amount Rup. " << ceil(amount) << endl;
    }
};

class EMIPayment : public PaymentStrategy
{
public:
    EMIPayment()
    {
        cout << "Credit Card Payment Initiated" << endl;
    }

    void process(double amount) override
    {
        cout << "Processing EMI payment of amount Rup. " << ceil(amount) << endl;
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
        paymentStrat = payStrat;
    }
    ~Payment() {}

    void processPayment()
    {
        if (amount > 0 && paymentStrat != nullptr)
        {
            paymentStrat->process(amount);
        }
        else
        {
            cout << "Invalid Payment amount" << endl;
        }
        return;
    }
};