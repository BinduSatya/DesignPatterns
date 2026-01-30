/*
Facade Design:
It Provides a Simplified, Unified interface to set a complex subsystems.
It hides the complexity of the system and exposes only what is necessary.


Its Intent is to hide the complexity of the child methods

Principle of Least Knowledge:
Whenever we take a object, this principle tells us to invoke only those
methods that belongs to:
1. The object itself.
2. The object that is passed into paranthesis for a method
3. Any object that the method created.
4. Any obect that this object has-a relationship with.

But not with any objects like A->c, when C is a child to child for A
A->B->C

- If A wants something from C, then A should call to B, and then
B should call to C, to get that data and return to A. So that this 
principle is promoting Loose Coupling between classes
*/

#include <bits/stdc++.h>
using namespace std;

class PowerSupply
{
public:
    void providePower()
    {
        cout << "Power Supply: Providing Power" << endl;
    }
};

class CoolingSystem
{
public:
    void startFans()
    {
        cout << "Cooling System: Turning On Fans" << endl;
    }
};

class CPU
{
public:
    void initialize()
    {
        cout << "CPU: Initialization Started" << endl;
    }
};

class Memory
{
public:
    void selfTest()
    {
        cout << "Memory: Testing the memory" << endl;
    }
};

class Hardware
{
public:
    void spinUp()
    {
        cout << "Hardware: Spinning Up..." << endl;
    }
};

class OperatingSystem
{
public:
    void load()
    {
        cout << "Operating System: Loading the data into memory" << endl;
    }
};

class BIOS
{
public:
    void boot(CPU &cpu, Memory &mem)
    {

        cout << "Memory: Booting CPU and memory checks..." << endl;
        cpu.initialize();
        mem.selfTest();
    }
};

class ComputerFacade
{
private:
    PowerSupply powerSupply;
    CoolingSystem cooling;
    Memory mem;
    CPU cpu;
    Hardware hardware;
    BIOS bios;
    OperatingSystem os;

public:
    void startComputer()
    {
        cout << "Computer Starting..." << endl;
        powerSupply.providePower();
        cooling.startFans();
        hardware.spinUp();
        bios.boot(cpu, mem);
        os.load();
        cout << "Computer Started...";
    }
};

int main()
{
    ComputerFacade *computerFac = new ComputerFacade();
    computerFac->startComputer();
}