
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ========== DECORATOR PATTERN ==========

// Common interface
class INotification {
public:
    virtual string getContent() const = 0;
    virtual ~INotification() = default;
};

// Original notification
class SimpleNotification : public INotification {
    string message;

public:
    SimpleNotification(string msg) {
        message = msg;
    }

    string getContent() const override {
        return message;
    }
};

// Parent decorator
class NotificationDecorator : public INotification {
protected:
    INotification* notification;

public:
    NotificationDecorator(INotification* n) {
        notification = n;
    }

    virtual ~NotificationDecorator() {
        delete notification;
    }
};

// Adds timestamp
class TimestampDecorator : public NotificationDecorator {
public:
TimestampDecorator(INotification* n) {
    notification = n;
}
    string getContent() const override {
        return "[2026-11-03 10:00] " + notification->getContent();
    }
};

// Adds signature
class SignatureDecorator : public NotificationDecorator {
    string signature;

public:
 SignatureDecorator(INotification* n, string sig) {
    notification = n;
    signature = sig;
}

    string getContent() const override {
        return notification->getContent() + "\n-- " + signature;
    }
};


// ========== OBSERVER PATTERN ==========

class IObserver {
public:
    virtual void update() = 0;
    virtual ~IObserver() = default;
};

class NotificationObservable {
    vector<IObserver*> observers;
    INotification* currentNotification = nullptr;

public:
    void addObserver(IObserver* obs) {
        observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) {
        observers.erase(
            remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void setNotification(INotification* n) {
        delete currentNotification;
        currentNotification = n;

        for (IObserver* obs : observers) {
            obs->update();
        }
    }

    string getNotificationContent() const {
        return currentNotification->getContent();
    }

    ~NotificationObservable() {
        delete currentNotification;
    }
};


// Observer 1: Logger
class Logger : public IObserver {
    NotificationObservable* observable;

public:
    Logger(NotificationObservable* o) {
        observable = o;
    }

    void update() override {
        cout << "\nLogging notification:\n";
        cout << observable->getNotificationContent() << "\n";
    }
};


// ========== STRATEGY PATTERN ==========

class INotificationStrategy {
public:
    virtual void sendNotification(const string& content) = 0;
    virtual ~INotificationStrategy() = default;
};

// Email strategy
class EmailStrategy : public INotificationStrategy {
    string email;

public:
    EmailStrategy(string e) {
        email = e;
    }

    void sendNotification(const string& content) override {
        cout << "\nSending Email to " << email << "\n";
        cout << content << "\n";
    }
};

// SMS strategy
class SMSStrategy : public INotificationStrategy {
    string mobile;

public:
    SMSStrategy(string m) {
        mobile = m;
    }

    void sendNotification(const string& content) override {
        cout << "\nSending SMS to " << mobile << "\n";
        cout << content << "\n";
    }
};

// Popup strategy
class PopupStrategy : public INotificationStrategy {
public:
    void sendNotification(const string& content) override {
        cout << "\nShowing Popup:\n";
        cout << content << "\n";
    }
};


// Observer 2: Notification Engine
class NotificationEngine : public IObserver {
    NotificationObservable* observable;
    vector<INotificationStrategy*> strategies;

public:
    NotificationEngine(NotificationObservable* o) {
        observable = o;
    }

    void addStrategy(INotificationStrategy* s) {
        strategies.push_back(s);
    }

    void update() override {
        string content = observable->getNotificationContent();

        for (auto s : strategies) {
            s->sendNotification(content);
        }
    }

    ~NotificationEngine() {
        for (auto s : strategies) {
            delete s;
        }
    }
};


// ========== SINGLETON PATTERN ==========

class NotificationService {
    NotificationObservable observable;

    NotificationService() {}

public:
    static NotificationService& getInstance() {
        static NotificationService instance;
        return instance;
    }

    NotificationObservable* getObservable() {
        return &observable;
    }

    void sendNotification(INotification* n) {
        observable.setNotification(n);
    }
};


// ========== MAIN ==========

int main() {

    // Get the single NotificationService object
    NotificationService& service = NotificationService::getInstance();

    // Get observable
    NotificationObservable* observable = service.getObservable();

    // Create observers
    Logger logger(observable);
    NotificationEngine engine(observable);

    // Add delivery strategies
    engine.addStrategy(new EmailStrategy("user@gmail.com"));
    engine.addStrategy(new SMSStrategy("+91 9876543210"));
    engine.addStrategy(new PopupStrategy());

    // Register observers
    observable->addObserver(&logger);
    observable->addObserver(&engine);

    // Create notification
    INotification* notification =
        new SimpleNotification("Your order has been shipped!");

    // Add decorators
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");

    // Send notification
    service.sendNotification(notification);

    return 0;
}
