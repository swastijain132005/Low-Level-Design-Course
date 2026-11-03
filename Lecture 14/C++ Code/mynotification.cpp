
#include <iostream>
#include <vector>
using namespace std;

// ========== DECORATOR ==========

class Notification {
public:
    virtual string getMessage() = 0;
    virtual ~Notification() {}
};

class SimpleNotification : public Notification {
public:
    string getMessage() override {
        return "Order Shipped!";
    }
};

class Decorator : public Notification {
protected:
    Notification* n;

public:
    Decorator(Notification* obj) {
        n = obj;
    }

    virtual ~Decorator() {
        delete n;
    }
};

class Timestamp : public Decorator {
public:
    Timestamp(Notification* obj) {
        n = obj;
    }

    string getMessage() override {
        return "[10:00 AM] " + n->getMessage();
    }
};

class Signature : public Decorator {
public:
    Signature(Notification* obj) {
        n = obj;
    }

    string getMessage() override {
        return n->getMessage() + " - Customer Care";
    }
};


// ========== STRATEGY ==========

class Strategy {
public:
    virtual void send(string msg) = 0;
    virtual ~Strategy() {}
};

class Email : public Strategy {
public:
    void send(string msg) override {
        cout << "Email: " << msg << endl;
    }
};

class SMS : public Strategy {
public:
    void send(string msg) override {
        cout << "SMS: " << msg << endl;
    }
};

class Popup : public Strategy {
public:
    void send(string msg) override {
        cout << "Popup: " << msg << endl;
    }
};


// ========== OBSERVER ==========

class Observer {
public:
    virtual void update(string msg) = 0;
    virtual ~Observer() {}
};

class Logger : public Observer {
public:
    void update(string msg) override {
        cout << "Log: " << msg << endl;
    }
};

class NotificationEngine : public Observer {
    vector<Strategy*> strategies;

public:
    void addStrategy(Strategy* s) {
        strategies.push_back(s);
    }

    void update(string msg) override {
        for (auto s : strategies) {
            s->send(msg);
        }
    }

    ~NotificationEngine() {
        for (auto s : strategies) {
            delete s;
        }
    }
};


// ========== SINGLETON ==========

class NotificationService {
    vector<Observer*> observers;

    NotificationService() {}

public:
    NotificationService(const NotificationService&) = delete;
    void operator=(const NotificationService&) = delete;

    static NotificationService& getInstance() {
        static NotificationService service;
        return service;
    }

    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void send(Notification* n) {
        string msg = n->getMessage();

        for (auto o : observers) {
            o->update(msg);
        }

        delete n;
    }
};


// ========== MAIN ==========

int main() {

    NotificationService& service =
        NotificationService::getInstance();

    Logger logger;
    NotificationEngine engine;

    service.addObserver(&logger);
    service.addObserver(&engine);

    engine.addStrategy(new Email());
    engine.addStrategy(new SMS());
    engine.addStrategy(new Popup());

    Notification* n = new SimpleNotification();

    n = new Timestamp(n);
    n = new Signature(n);

    service.send(n);

    return 0;
}
