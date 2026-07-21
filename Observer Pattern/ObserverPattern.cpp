#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*==========================
    Observer Interface
==========================*/
class Observer {
public:
    virtual void update(const string& channelName,
                        const string& videoTitle) = 0;

    virtual ~Observer() = default;
};

/*==========================
      Concrete Observer
==========================*/

class EmailObserver : public Observer {
private:
    string email;

public:
    EmailObserver(const string& email)
        : email(email) {}

    void update(const string& channelName,
                const string& videoTitle) override {

        cout << "[Email] Send to "
             << email
             << "\n"
             << " Channel: " << channelName
             << "\n New Video: "
             << videoTitle << "\n\n";
    }
};

class SMSObserver : public Observer {
private:
    string phone;

public:
    SMSObserver(const string& phone)
        : phone(phone) {}

    void update(const string& channelName,
                const string& videoTitle) override {

        cout << "[SMS] Send to "
             << phone
             << "\n"
             << " Channel: " << channelName
             << "\n New Video: "
             << videoTitle << "\n\n";
    }
};

class PushObserver : public Observer {
private:
    string deviceToken;

public:
    PushObserver(const string& token)
        : deviceToken(token) {}

    void update(const string& channelName,
                const string& videoTitle) override {

        cout << "[Push Notification]"
             << "\n Device: "
             << deviceToken
             << "\n Channel: "
             << channelName
             << "\n New Video: "
             << videoTitle << "\n\n";
    }
};

/*==========================
        Subject
==========================*/

class Subject {
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify(const string& videoTitle) = 0;

    virtual ~Subject() = default;
};

/*==========================
    Concrete Subject
==========================*/

class YoutubeChannel : public Subject {
private:
    string channelName;

    vector<Observer*> observers;

public:
    YoutubeChannel(const string& name)
        : channelName(name) {}

    void attach(Observer* observer) override {
        observers.push_back(observer);
    }

    void detach(Observer* observer) override {
        observers.erase(
            remove(observers.begin(),
                   observers.end(),
                   observer),
            observers.end());
    }

    void notify(const string& videoTitle) override {

        for (Observer* observer : observers)
            observer->update(channelName, videoTitle);
    }

    void uploadVideo(const string& videoTitle) {

        cout << "\n=============================================\n";
        cout << "Channel [" << channelName
             << "] uploaded: "
             << videoTitle << endl;
        cout << "=============================================\n";

        notify(videoTitle);
    }
};

/*==========================
            Main
==========================*/

int main() {

    YoutubeChannel apcs("APCS Free Course");

    EmailObserver email1("alice@gmail.com");
    EmailObserver email2("bob@gmail.com");

    SMSObserver sms1("+84901234567");

    PushObserver push1("DEVICE_TOKEN_001");

    // Subscribe
    apcs.attach(&email1);
    apcs.attach(&email2);
    apcs.attach(&sms1);
    apcs.attach(&push1);

    apcs.uploadVideo("Introduction to Observer Pattern");

    cout << "\n======= Bob unsubscribes =======\n\n";

    apcs.detach(&email2);

    apcs.uploadVideo("Observer Pattern Deep Dive");

    return 0;
}
