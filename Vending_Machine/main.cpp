/*
VENDING MACHINE DESIGN
We are implementing State Design Pattern here as thinking
machine has different states with user interactions

Interactions:
1. User inserts coin in the machine.
2. User can select the drink he wants.
3. Machine validates the coin value to the drink value and returns
whether the response
4. Machine dispatches the drink user wanted and checks the inventory
5. If the inventory is empty, it won't take any more requests/coins
from user.
6. If the inventory is not empty, machine goes to its initial state.

States of Machine:
1. NoCoin State - Where there is no coin in the machine and the only task that the machine can accept is taking coin from user.
2. HasCoin State - The point when user inserts coin and then the changes to HasCoin state where the system should take the user request to select the drink.
3. Dispatch State - The state of machine where machine dispatches the drink that user selected and also returns the extra money (if applicable). At this point the machine won't take any coins and don't allow user to select the drink.
4. Empty State - After dispatching the drink user wants, if there is no stock present in the machine, then the machines changes its state to Empty State, where it won't accept any requests from user.
*/

#include <bits/stdc++.h>
#include "Vending_Machine.cpp"
using namespace std;

int main()
{
    VendingMachine vm;

    vm.addDrinks("coke", 10, 2);
    vm.addDrinks("pepsi", 15, 1);

    vm.selectDrink("coke");

    vm.insertCoin(5);
    vm.selectDrink("coke");

    vm.insertCoin(5);
    vm.selectDrink("coke");
    vm.dispatchDrink();

    vm.insertCoin(10);
    vm.selectDrink("coke");
    vm.dispatchDrink();

    vm.insertCoin(10);
    vm.selectDrink("coke");
    vm.returnCoins();

    vm.insertCoin(20);
    vm.selectDrink("pepsi");
    vm.dispatchDrink();

    vm.insertCoin(10);
    vm.selectDrink("pepsi");

    vm.getAllDrinks();

    return 0;
}
