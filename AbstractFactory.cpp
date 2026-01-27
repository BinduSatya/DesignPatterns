#include <bits/stdc++.h>
using namespace std;

class Button
{
public:
    virtual void render() = 0;
};
class Checkbox
{
public:
    virtual void toggle() = 0;
};

class WindowsButton : public Button
{
public:
    void render() override
    {
        cout << "Rendering Windows Button" << endl;
    }
};

class WindowsCheckbox : public Checkbox
{
public:
    void toggle() override
    {
        cout << "Toggling Windows Checkbox" << endl;
    }
};

class MacButton : public Button
{
public:
    void render() override
    {
        cout << "Rendering Mac Button" << endl;
    }
};

class MacCheckbox : public Checkbox
{
public:
    void toggle() override
    {
        cout << "Toggling Mac Checkbox" << endl;
    }
};

class UIFactory
{
public:
    virtual Button *createButton() = 0;
    virtual Checkbox *createCheckbox() = 0;
};

class WindowsFactory : public UIFactory
{
public:
    Button *createButton() override
    {
        return new WindowsButton();
    }
    Checkbox *createCheckbox() override
    {
        return new WindowsCheckbox();
    }
};

class MacFactory : public UIFactory
{
public:
    Button *createButton() override
    {
        return new MacButton();
    }
    Checkbox *createCheckbox() override
    {
        return new MacCheckbox();
    }
};

int main()
{
    UIFactory *factory;
    string os;
    cout << "Enter OS (Windows/Mac): ";
    cin >> os;

    if (os == "windows")
        factory = new WindowsFactory();
    else
        factory = new MacFactory();

    Button *button = factory->createButton();
    Checkbox *checkbox = factory->createCheckbox();

    button->render();
    checkbox->toggle();
    return 0;
}