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
