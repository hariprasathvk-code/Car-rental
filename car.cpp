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
