#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


struct User {
    string username;
    string password;
};

const string USER_DB = "users.csv";
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

//  Function Declarations 
void initialization();
void process(bool isAdmin);
void termination();

// Admin flow
void adminLoginProcess();
bool validateAdminPassword();
void chooseAdminApplication();
void updateCarLibrary();
void answerCustomerEnquiries();
void logout();

// User flow
void userLoginProcess();
void newUser();
bool checkPasswordCorrect(string username);
void requestNewPassword(string username);
void userActivities(string username);

// CSV helpers
bool loadUsers(vector<User>& users);
void saveUser(const User& user);

//  MAIN 
int main() {
    initialization();
    termination();
    return 0;
}

//  Initialization 
void initialization() {
    cout << "\n=== Initialization ===\n";
    cout << "Are you Admin? (y/n): ";
    char choice; cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        process(true);   // ALP
    } else {
        cout << "Are you a registered user? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            process(false);  // ULP
        } else {
            newUser();       
            return;          
        }
    }
}

// Process
void process(bool isAdmin) {
    cout << "\n=== Process (P) ===\n";
    if (isAdmin) adminLoginProcess();
    else userLoginProcess();
}

//  Admin Login Process (ALP) 
void adminLoginProcess() {
    cout << "\n=== Admin Login Process (ALP) ===\n";

    if (!validateAdminPassword()) {
        cout << "Retrying Admin Login...\n";
        adminLoginProcess();   
        return;
    }

    chooseAdminApplication();
}

bool validateAdminPassword() {
    string uname, pass;
    cout << "Enter Admin Username: ";
    cin >> uname;
    cout << "Enter Admin Password: ";
    cin >> pass;

    if (uname == ADMIN_USERNAME && pass == ADMIN_PASSWORD) {
        cout << "Admin authenticated successfully!\n";
        return true;
    }
    cout << "Incorrect Admin Credentials!\n";
    return false;
}

void chooseAdminApplication() {
    int choice;
    do {
        cout << "\n Admin portal\n";
        cout << "1. Update Car Library\n";
        cout << "2. Answer Customer Enquiries\n";
        cout << "3. Logout\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: updateCarLibrary(); break;
            case 2: answerCustomerEnquiries(); break;
            case 3: logout(); return;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

void updateCarLibrary() {
    cout << "[Admin] Car Library has been updated successfully!\n";
}

void answerCustomerEnquiries() {
    cout << "[Admin] Customer enquiries have been responded successfully!\n";
}

void logout() {
    cout << "[Admin] Logged out successfully.\n";
}
