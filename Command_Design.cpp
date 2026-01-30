/*
Command Design:
It is a behavioural design pattern, in which a object is used to
encapsulate all information needed to perform an action or trigger
an event at a later time.

The information can be method name, the object that owns the method,
and values for the method parameters.
*/

#include <bits/stdc++.h>
using namespace std;

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

class Music
{
private:
    int volume;
    float station;

public:
    Music() : volume(5), station(98.5f) {}

    void setVolume(int vol)
    {
        cout << "Setting volume to: " << vol << endl;
        volume = vol;
    }

    void setStation(float st)
    {
        cout << "Setting station to: " << st << endl;
        station = st;
    }

    void on()
    {
        cout << "Turning ON the music system" << endl;
    }

    void off()
    {
        cout << "Turning OFF the music system" << endl;
    }
};

class MusicOnCommand : public Command
{
private:
    Music *music;

public:
    MusicOnCommand(Music *m) : music(m) {}

    void execute() override
    {
        music->on();
    }
};

class MusicOffCommand : public Command
{
private:
    Music *music;

public:
    MusicOffCommand(Music *m) : music(m) {}

    void execute() override
    {
        music->off();
    }
};

class SetVolumeCommand : public Command
{
private:
    Music *music;
    int volume;

public:
    SetVolumeCommand(Music *m, int v) : music(m), volume(v) {}

    void execute() override
    {
        music->setVolume(volume);
    }
};

class SetStationCommand : public Command
{
private:
    Music *music;
    float station;

public:
    SetStationCommand(Music *m, float s) : music(m), station(s) {}

    void execute() override
    {
        music->setStation(station);
    }
};

class RemoteControl
{
private:
    Command *command;

public:
    void setCommand(Command *cmd)
    {
        command = cmd;
    }

    void pressButton()
    {
        if (command)
            command->execute();
    }
};

int main()
{
    Music musicSystem;

    MusicOnCommand onCmd(&musicSystem);
    MusicOffCommand offCmd(&musicSystem);
    SetVolumeCommand volumeCmd(&musicSystem, 10);
    SetStationCommand stationCmd(&musicSystem, 101.2f);

    RemoteControl remote;

    remote.setCommand(&onCmd);
    remote.pressButton();

    remote.setCommand(&volumeCmd);
    remote.pressButton();

    remote.setCommand(&stationCmd);
    remote.pressButton();

    remote.setCommand(&offCmd);
    remote.pressButton();

    return 0;
}
