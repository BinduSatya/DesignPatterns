#include <bits/stdc++.h>
using namespace std;
class NotificationService;
class INotificaton
{
public:
    virtual string getContent() = 0;
    virtual ~INotificaton() = default;
};

class SimpleNotification : public INotificaton
{
private:
    string text;

public:
    SimpleNotification(string msg)
    {
        this->text = msg;
    }

    string getContent() override
    {
        return text;
    }
};

class NotificationDecorator : public INotificaton
{
protected:
    INotificaton *notification;

public:
    NotificationDecorator(INotificaton *noti)
    {
        notification = noti;
    }

    string getContent() override
    {
        return notification->getContent();
    }
};

class TimeStampDecorator : public NotificationDecorator
{
public:
    TimeStampDecorator(INotificaton *noti) : NotificationDecorator(noti)
    {
    }

    string getContent() override
    {
        return "[11:20 pm IST]" + notification->getContent();
    }
};

class SignatureDecorator : public NotificationDecorator
{
public:
    SignatureDecorator(INotificaton *noti) : NotificationDecorator(noti) {}
    string getContent() override
    {
        return "BinduSatya:" + notification->getContent();
    }
};

class IObserver
{
public:
    virtual void update() = 0;
    virtual ~IObserver() = default;
};

class IObservable
{
public:
    virtual void addObserver(IObserver *obs) = 0;
    virtual void removeObserver(IObserver *obs) = 0;
    virtual void notifyObserver() = 0;
    ~IObservable() = default;
};

class NotificationObservable : public IObservable
{
private:
    vector<IObserver *> observers;
    INotificaton *currentNotification;

public:
    NotificationObservable()
    {
        currentNotification = nullptr;
    }

    void addObserver(IObserver *obs) override
    {
        observers.push_back(obs);
    }

    void removeObserver(IObserver *obs) override
    {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObserver() override
    {
        for (auto obs : observers)
        {
            obs->update();
        }
    }

    void setNotification(INotificaton *notification)
    {
        this->currentNotification = notification;
        notifyObserver();
    }

    INotificaton *getNotification()
    {
        return currentNotification;
    }

    string getNotificationContent()
    {
        return currentNotification->getContent();
    }

    ~NotificationObservable()
    {
        delete currentNotification;
    }
};

class NotificationService
{
private:
    NotificationObservable *observable;
    static NotificationService *instance;
    vector<INotificaton *> notifications;

    NotificationService()
    {
        observable = new NotificationObservable();
    }

public:
    static NotificationService *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new NotificationService();
        }
        return instance;
    }

    NotificationObservable *getObservable()
    {
        return observable;
    }

    void sendNotification(INotificaton *notification)
    {
        notifications.push_back(notification);
        observable->setNotification(notification);
    }

    ~NotificationService()
    {
        for (auto n : notifications)
            delete n;
        delete observable;
    }
};

NotificationService *NotificationService::instance = nullptr;

class Logger : public IObserver
{
private:
    NotificationObservable *observable;

public:
    Logger()
    {
        observable = NotificationService::getInstance()->getObservable();
        observable->addObserver(this);
    }

    void update()
    {
        cout << "New Notification:" << observable->getNotificationContent() << endl;
    }
};

class INotificationStrategy
{
public:
    virtual void sendNotification(string content) = 0;
};

class EmailStrategy : public INotificationStrategy
{
private:
    string emailId;

public:
    EmailStrategy(string e)
    {
        emailId = e;
    }

    void sendNotification(string content) override
    {
        cout << "Sending Email Notification to:" << emailId << endl;
        cout << "Content:  " << content << endl;
    }
};

class SMSStrategy : public INotificationStrategy
{
private:
    string phoneNumber;

public:
    SMSStrategy(string phn)
    {
        phoneNumber = phn;
    }
    void sendNotification(string content) override
    {
        cout << "Sending SMS Notification to:" << phoneNumber << endl;
        cout << "Content:  " << content << endl;
    }
};

class PopUpStrategy : public INotificationStrategy
{
public:
    void sendNotification(string content) override
    {
        cout << "Sending Pop Up Notification " << endl;
        cout << "Content:  " << content << endl;
    }
};

class NotificationEngine : public IObserver
{
private:
    vector<INotificationStrategy *> strategies;
    NotificationObservable *observable;

public:
    NotificationEngine()
    {
        this->observable = NotificationService::getInstance()->getObservable();
        observable->addObserver(this);
    }

    void addNotificationStrategy(INotificationStrategy *str)
    {
        strategies.push_back(str);
    }

    void update() override
    {
        string notificationContent = observable->getNotificationContent();
        for (auto it : strategies)
        {
            it->sendNotification(notificationContent);
        }
    }
};

int main()
{
    NotificationService *notificationService = NotificationService::getInstance();
    IObserver *logger = new Logger();
    NotificationEngine *notificationEngine = new NotificationEngine();
    notificationEngine->addNotificationStrategy(new EmailStrategy("bsa@gmail.com"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());
    notificationEngine->addNotificationStrategy(new SMSStrategy("1234567"));

    INotificaton *notification1 = new SimpleNotification("Hello bindu");
    INotificaton *notification2 = new SimpleNotification("Hello satya");
    notification2 = new TimeStampDecorator(notification2);

    notificationService->sendNotification(notification1);
    notificationService->sendNotification(notification2);

    delete logger;
    delete notificationEngine;
    delete notification1;
    delete notification2;
}