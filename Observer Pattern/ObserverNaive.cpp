#include <iostream>
#include <vector>
#include <string>
using namespace std;

class EmailService {
public:
    void sendEmailNoti(const string& emailAddress, const string& videoTitle){
        cout << "[Email Service] Sending email to " << emailAddress
            << ": New video '" << videoTitle << " is out now!\n";
    }
};

class SMSService {
public:
    void sendSMSNoti(const string& phoneNum, const string& videoTitle){
        cout << "[SMS Service] Sending SMS to " << phoneNum
            << ": New video '" << videoTitle << " is out now!\n";
    }
};

class PushService {
public:
    void sendPushNoti(const string& deviceToken, const string& videoTitle){
        cout << "[Push Service] Sending push to " << deviceToken
            << ": New video '" << videoTitle << " is out now!\n";
    }
};

class YoutubeChannel {
private:
    string channelName;

    // Tight Coupling (Has-A relationship)
    EmailService emailService;
    SMSService smsService;
    PushService pushService;

    // Hardcoded single-user data
    string userEmail = "idk@gmail.com";
    string userPhone = "+84901234567";
    string userDeviceToken = "DEVICE_TOKEN_ABC_123";

    // Manual flags for preferences
    bool isEmail = true;
    bool isSMS = true;
    bool isPush = true;
public:
    YoutubeChannel() : channelName("") {}
    YoutubeChannel(const string name) : channelName(name) {}

    void setSMSNoti(bool enable) {
        isSMS = enable;
    }

    // Violation of Open/Closed Principle (OCP)
    void sendNoti(const string& videoTitle) {
        if (isEmail) {
            emailService.sendEmailNoti(userEmail, videoTitle);
        }
        if (isSMS) {
            smsService.sendSMSNoti(userPhone, videoTitle);
        }
        if (isPush) {
            pushService.sendPushNoti(userDeviceToken, videoTitle);
        }
    }

    void uploadVideo(const string& videoTitle) {
        cout << "\n=============================================================\n";
        cout << " Channel [" << channelName << "] has just uploaded: " << videoTitle << "\n";
        cout << "=============================================================\n";
        sendNoti(videoTitle);

    }
};

int main(){
    YoutubeChannel myChannel("APCS Free Course");
    // Upload new video
    myChannel.uploadVideo("Introduction to Observer Pattern");

    // User disables SMS noti
    cout << "\n--> User A disables SMS notifications...\n";
    myChannel.setSMSNoti(false);
    myChannel.uploadVideo("Observer Pattern Deep Dive");

    return 0;
}