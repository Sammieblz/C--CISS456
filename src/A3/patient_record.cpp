#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <regex>
#include <sqlite3.h>


using namespace std;

const std::regex SSN_REGEX("\\d{9}");
const std::regex NAME_REGEX("[a-zA-Z]+");
const std::regex ADDRESS_REGEX("[a-zA-Z0-9 ]+");
const std::regex ZIP_REGEX("\\d{5}");

class Patient {
private:
    string ssn;
    string firstName;
    string lastName;
    char middleInitial;
    string address;
    string city;
    string state;
    string zip;

public:
    // Constructor to initialize patient data
    Patient() : ssn(""), firstName(""), lastName(""), middleInitial('\0'),
                address(""), city(""), state(""), zip("") {}

    // Function to input patient data
    void inputData() {
        std::smatch match;
        cout << "Enter SSN (9 digits): ";
        cin >> ssn;
        // Validate SSN format
        while (!std::regex_match(ssn, SSN_REGEX)) {
            cout << "Invalid SSN. Please enter again: ";
            cin >> ssn;
        }

        cout << "Enter first name: ";
        cin >> firstName;
        // Validate first name format
        while (!std::regex_match(firstName, NAME_REGEX)) {
            cout << "Invalid name. Please enter again: ";
            cin >> firstName;
        }

        cout << "Enter last name: ";
        cin >> lastName;
        // Validate last name format
        while (!std::regex_match(lastName, NAME_REGEX)) {
            cout << "Invalid name. Please enter again: ";
            cin >> lastName;
        }

        cout << "Enter middle initial: ";
        cin >> middleInitial;

        cin.ignore(); // Ignore newline character
        cout << "Enter address: ";
        getline(cin, address);
        // Validate address format
        while (!std::regex_match(address, ADDRESS_REGEX)) {
            cout << "Invalid address. Please enter again: ";
            getline(cin, address);
        }

        cout << "Enter city: ";
        cin >> city;
        // Validate city format
        while (!std::regex_match(city, NAME_REGEX)) {
            cout << "Invalid city. Please enter again: ";
            cin >> city;
        }

        cout << "Enter state code (2 characters): ";
        cin >> state;

        while (isValidState(state) == false)
        {
            cout << "ERROR: Invalid State" << '\n';
            cout << "Enter state code (2 characters): ";
            cin >> state;
            isValidState(state);
        }

        cout << "Enter ZIP code: ";
        cin >> zip;
        // Validate ZIP code format
        while (!std::regex_match(zip, ZIP_REGEX)) {
            cout << "Invalid ZIP code. Please enter again: ";
            cin >> zip;
        }
    }

    bool isValidState(string state) {
        sqlite3 *db;
        sqlite3_stmt *stmt;

        // Open the SQLite database
        int rc = sqlite3_open("chinook.db", &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return false;
        }

        // Prepare SQL statement
        const char *sql = "SELECT COUNT(*) FROM states WHERE StateCodes = ?";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return false;
        }

        // Bind parameter
        rc = sqlite3_bind_text(stmt, 1, state.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return false;
        }

        // Execute statement
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int count = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return count > 0;
        } else {
            std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return false;
        }
}

    // Function to get SSN
    string getSSN() const {
        return ssn;
    }

    // Function to get patient information as a formatted string
    string getInfoString() const {
        return ssn + ", " + firstName + ", " + lastName + ", " +
               middleInitial + ", " + address + ", " + city + ", " +
               state + ", " + zip;
    }
};

class FileManager {
public:
    // Function to write patient record to file
    static void writeToFile(const Patient& patient, const string& filename) {
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << patient.getInfoString() << '\n';
            cout << "Record written to file successfully.\n";
            outFile.close();
        } else {
            cout << "Unable to open file.\n";
        }
    }
};

int main() {
    char choice;
    string filename = "patient_records.csv";

    do {
        Patient patient;
        patient.inputData();
        FileManager::writeToFile(patient, filename);

        cout << "Do you want to enter another record? (Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    return 0;
}
