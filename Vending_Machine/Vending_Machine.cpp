#include <bits/stdc++.h>
using namespace std;

class VendingMachine;
class NoCoinState;
class HasCoinState;
class DisPatchingState;
class EmptyState;

class VendingMachineState
{
public:
    virtual VendingMachineState *insertCoin(VendingMachine *machine, int amount)
    {
        cout << "Nothing happens\n";
        return this;
    }
    virtual VendingMachineState *selectDrink(VendingMachine *machine, string &drink)
    {
        cout << "Nothing happens\n";
        return this;
    }
    virtual VendingMachineState *dispatchDrink(VendingMachine *machine)
    {
        cout << "Nothing happens\n";
        return this;
    }
    virtual VendingMachineState *changeToEmpty()
    {
        cout << "Nothing happens\n";
        return this;
    }

    virtual VendingMachineState *returnCoins(VendingMachine *machine)
    {
        cout << "Nothing happens\n";
        return this;
    }

    virtual ~VendingMachineState() = default;
};

class NoCoinState : public VendingMachineState
{
public:
    NoCoinState()
    {
        cout << "State changed to no coin" << endl;
    }
    VendingMachineState *insertCoin(VendingMachine *machine, int amount) override;
};

class HasCoinState : public VendingMachineState
{
public:
    HasCoinState()
    {
        cout << "State changed to Has coin" << endl;
    }

    VendingMachineState *insertCoin(VendingMachine *machine, int amount) override;
    VendingMachineState *selectDrink(VendingMachine *machine, string &drink) override;
    VendingMachineState *returnCoins(VendingMachine *machine) override;
};

class DisPatchingState : public VendingMachineState
{
public:
    DisPatchingState()
    {
        cout << "State changed to Dispatch" << endl;
    }
    VendingMachineState *dispatchDrink(VendingMachine *machine) override;
    VendingMachineState *resetSelection(VendingMachine *machine);
};

class EmptyState : public VendingMachineState
{
public:
    EmptyState()
    {
        cout << "State changed to Empty" << endl;
    }
};

class VendingMachine
{
private:
    VendingMachineState *state;
    VendingMachineState *noCoinState;
    VendingMachineState *hasCoinState;
    VendingMachineState *emptyState;
    VendingMachineState *dispatchingState;

    int coins;
    string selectedDrink;

    struct Drink
    {
        int price;
        int quantity;
    };

    unordered_map<string, Drink> drinks;

public:
    int getAllDrinks() const
    {
        int tot = 0;
        for (auto &it : drinks)
        {
            cout << it.first << ": " << it.second.quantity << endl;
            tot += it.second.quantity;
        }
        return tot;
    }

    int getDrinkQnty(const string &drink)
    {
        auto it = drinks.find(drink);
        if (it == drinks.end())
            return 0;

        return it->second.quantity;
    }

    double getDrinkPrice(string &drink)
    {
        double price = drinks[drink].price;
        return price;
    }

    void reduceDrinks(string &drink)
    {
        if (drinks.find(drink) != drinks.end())
            drinks[drink].quantity--;
        resetCoins();
    }

    void resetCoins()
    {
        cout << "Remaining amount will be refunded" << endl;
        coins = 0;
    }

    int getCoins()
    {
        return this->coins;
    }

    void addCoins(int add)
    {
        if (add > 0)
        {
            cout << "Added: " << add << endl;
            this->coins = this->coins + add;
            return;
        }

        else
        {
            cout << "Please insert valid coins" << endl;
        }
    }

    void addDrinks(string drinkName, int qnty, int price)
    {
        if (qnty > 0 && price > 0)
        {
            drinks[drinkName].quantity += qnty;
            drinks[drinkName].price = price;
            cout
                << "Adding " << qnty << " " << drinkName << "  drinks" << endl;
        }
        else
        {
            cout << "Please pass valid qnty" << endl;
        }
    }

    string getSelectedDrink()
    {
        return selectedDrink;
    }

    void setSelectedDrink(string drink)
    {
        selectedDrink = drink;
    }

    VendingMachineState *getNoCoinState() { return noCoinState; }
    VendingMachineState *getHasCoinState() { return hasCoinState; }
    VendingMachineState *getDispatchingState() { return dispatchingState; }
    VendingMachineState *getEmptyState() { return emptyState; }

    VendingMachine()
    {
        cout << "A new Vending Machine is created" << endl;
        this->noCoinState = new NoCoinState();
        this->hasCoinState = new HasCoinState();
        this->dispatchingState = new DisPatchingState();
        this->emptyState = new EmptyState();
        coins = 0;
        selectedDrink = "";
        drinks.clear();
        state = noCoinState;
    }

    void insertCoin(int amount)
    {
        state = state->insertCoin(this, amount);
    };

    void returnCoins()
    {
        state = state->returnCoins(this);
    }

    void selectDrink(string drink)
    {
        state = state->selectDrink(this, drink);
    };

    void dispatchDrink()
    {
        state = state->dispatchDrink(this);
    }

    ~VendingMachine()
    {
        delete noCoinState;
        delete hasCoinState;
        delete dispatchingState;
        delete emptyState;
    }
};

VendingMachineState *NoCoinState::insertCoin(VendingMachine *machine, int amount)
{
    machine->addCoins(amount);
    cout << "Your total amount is " << machine->getCoins() << endl;
    return machine->getHasCoinState();
}

VendingMachineState *HasCoinState::selectDrink(VendingMachine *machine, string &drink)
{
    int qnty = machine->getDrinkQnty(drink);
    int costPrice = machine->getDrinkPrice(drink);

    if (qnty == 0)
    {
        cout << "This drink is not available now" << endl;
        return machine->getHasCoinState();
    }

    if (machine->getCoins() < costPrice)
    {
        cout << "Not Enough Money to buy this drink" << endl;
        return machine->getHasCoinState();
    }
    machine->setSelectedDrink(drink);
    cout << "This drink costs " << costPrice << " do you want to dispatch?" << endl;
    return machine->getDispatchingState();
}

VendingMachineState *HasCoinState::insertCoin(VendingMachine *machine, int amount)
{
    machine->addCoins(amount);
    cout << "You inserted amount of " << amount << endl;
    return machine->getHasCoinState();
}

VendingMachineState *HasCoinState::returnCoins(VendingMachine *machine)
{
    cout << "Returning the money: " << machine->getCoins() << endl;
    machine->resetCoins();
    return machine->getNoCoinState();
}

VendingMachineState *DisPatchingState::dispatchDrink(VendingMachine *machine)
{
    cout << "Dispatching the drink" << endl;
    string drink = machine->getSelectedDrink();
    machine->reduceDrinks(drink);
    machine->resetCoins();
    if (machine->getAllDrinks() == 0)
        return machine->getEmptyState();
    else
        return machine->getNoCoinState();
}

VendingMachineState *DisPatchingState::resetSelection(VendingMachine *machine)
{
    machine->setSelectedDrink("");
    cout << "Resetting the selection" << endl;
    return machine->getHasCoinState();
}