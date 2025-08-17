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
    cout << "\n Welcome \n";
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
    cout << "\n Process (P)\n";
    if (isAdmin) adminLoginProcess();
    else userLoginProcess();
}

//  Admin Login Process (ALP) 
void adminLoginProcess() {
    cout << "\n Admin Login Process (ALP) \n";

    if (!validateAdminPassword()) {
        cout << "Retrying Admin Login\n";
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

// User Login Process (ULP) 
void userLoginProcess() {
    cout << "\n User Login Process (ULP) \n";

    vector<User> users;
    loadUsers(users);

    string username;
    cout << "Enter Username: ";
    cin >> username;

    bool found = false;
    for (auto &u : users) {
        if (u.username == username) {
            found = true;

            cout << "Forgot Password? (y/n): ";
            char c; cin >> c;

            if (c == 'y' || c == 'Y') {
                // Forgot password → set new one → then check login
                requestNewPassword(username);
                if (checkPasswordCorrect(username)) {
                    userActivities(username);
                } else {
                    cout << "Wrong password. Try login again.\n";
                    userLoginProcess();
                }
            } else {
                // Normal login → just check password
                if (checkPasswordCorrect(username)) {
                    userActivities(username);
                } else {
                    cout << "Wrong password. Try login again.\n";
                    userLoginProcess();
                }
            }
            break;
        }
    }

    if (!found) {
        cout << "User not found. Register first.\n";
        newUser();
    }
}
void newUser() {
    string username, password;
    cout << "\n New User Registration \n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    saveUser({username, password});
    cout << "User registered successfully!\n";

    // After registration, go to user activities
    userActivities(username);
}

bool checkPasswordCorrect(string username) {
    vector<User> users;
    loadUsers(users);

    string password;
    cout << "Enter Password: ";
    cin >> password;

    for (auto &u : users) {
        if (u.username == username && u.password == password) {
            cout << "Login successful!\n";
            return true;
        }
    }
    return false;
}

void requestNewPassword(string username) {
    vector<User> users;
    loadUsers(users);

    string newPass;
    cout << "Enter new password for " << username << ": ";
    cin >> newPass;

    for (auto &u : users) {
        if (u.username == username) {
            u.password = newPass;
        }
    }

    // Rewrite DB
    ofstream file(USER_DB);
    for (auto &u : users) {
        file << u.username << "," << u.password << "\n";
    }
    file.close();
    cout << "Password updated successfully!\n";
}

void userActivities(string username) {
    int choice;
    do {
        cout << "\n User  (" << username << ") ---\n";
        cout << "1. Look for Vehicle\n";
        cout << "2. Make Payment\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "[User] Vehicle search completed.\n"; break;
            case 2: cout << "[User] Payment processed successfully.\n"; break;
            case 3: cout << "[User] Returning to main flow...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}

// Termination
void termination() {
    cout << "\n=== Termination ===\nReturning from Admin/User end.\n";
}

// CSV Helpers
bool loadUsers(vector<User>& users) {
    ifstream file(USER_DB);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string uname, pass;
        getline(ss, uname, ',');
        getline(ss, pass, ',');
        if (!uname.empty() && !pass.empty())
            users.push_back({uname, pass});
    }
    file.close();
    return true;
}

void saveUser(const User& user) {
    ofstream file(USER_DB, ios::app);
    file << user.username << "," << user.password << "\n";
    file.close();
}
