// ──────────────────────────────────────────
// UserAuth.cpp — Register & Login implementation
// ──────────────────────────────────────────

#include "UserAuth.h"
#include "Config.h"
#include "InputUtils.h"

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::ios;

// ── Check if email/phone already registered ──
bool UserAuth::userExists(std_compat::string_view email) {
    ifstream file(Config::USER_FILE);
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos) continue;

        // Zero-copy string slice using string_view
        std_compat::string_view lineView(line);
        std_compat::string_view storedEmail = lineView.substr(pos1 + 1, pos2 - pos1 - 1);
        if (storedEmail == email) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// ── Register a new user ──
bool UserAuth::registerUser() {
    string name, email, password, confirmPass;

    cout << "\n--------------------------------------------\n";
    cout << "            CREATE NEW ACCOUNT              \n";
    cout << "--------------------------------------------\n";

    clearInput();
    cout << "Enter Full Name          : ";
    getline(cin, name);

    if (name.empty()) {
        cout << "\n  Error: Name cannot be empty.\n";
        return false;
    }

    cout << "Enter Email or Phone No. : ";
    getline(cin, email);

    if (email.empty()) {
        cout << "\n  Error: Email/Phone cannot be empty.\n";
        return false;
    }

    // Reject pipe character to protect file-based record parsing
    if (name.find('|') != string::npos || email.find('|') != string::npos) {
        cout << "\n  Error: Name and Email cannot contain the '|' character.\n";
        return false;
    }

    // Check if user already exists
    if (userExists(email)) {
        cout << "\n  Error: An account with this email/phone already exists!\n";
        return false;
    }

    cout << "Create Password (min 4)  : ";
    getline(cin, password);

    if (password.length() < 4) {
        cout << "\n  Error: Password must be at least 4 characters.\n";
        return false;
    }

    if (password.find('|') != string::npos) {
        cout << "\n  Error: Password cannot contain the '|' character.\n";
        return false;
    }

    cout << "Confirm Password         : ";
    getline(cin, confirmPass);

    if (password != confirmPass) {
        cout << "\n  Error: Passwords do not match.\n";
        return false;
    }

    // Save to file
    ofstream file(Config::USER_FILE, ios::app);
    if (!file.is_open()) {
        cout << "\n  Error: Could not save user data.\n";
        return false;
    }
    file << name << "|" << email << "|" << password << "\n";
    file.close();

    cout << "\n  Account created successfully! Please login.\n";
    return true;
}

// ── Login an existing user ──
std_compat::optional<User> UserAuth::loginUser() {
    string email, password;

    cout << "\n--------------------------------------------\n";
    cout << "              LOGIN TO ACCOUNT              \n";
    cout << "--------------------------------------------\n";

    clearInput();
    cout << "Enter Email or Phone No. : ";
    getline(cin, email);

    cout << "Enter Password           : ";
    getline(cin, password);

    // Check credentials from file
    ifstream file(Config::USER_FILE);
    if (!file.is_open()) {
        cout << "\n  No registered users found. Please register first.\n";
        return {};
    }

    string line;
    while (getline(file, line)) {
        //  name|email|password
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string storedName  = line.substr(0, pos1);
        string storedEmail = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string storedPass  = line.substr(pos2 + 1);

        if (storedEmail == email && storedPass == password) {
            loggedInName  = storedName;
            loggedInEmail = storedEmail;
            file.close();
            cout << "\n  Login successful! Welcome, " << loggedInName << "!\n";
            return User(storedName, storedEmail);
        }
    }
    file.close();

    cout << "\n  Invalid email/phone or password.\n";
    return {};
}
