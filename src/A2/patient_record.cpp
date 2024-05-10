#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <regex>

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
        
        // Step 1: open .csv file
        ifstream stateFile("states.csv");

        // Step 2: validate if .csv file is open
        if(!stateFile.is_open()) std:cout << "ERROR: File Not Open";

        // Step 3: Validate data
        string stateCSV;

        while (stateFile.good())
        {
            while (getline(stateFile, stateCSV, '\n')) 
            {
                if (state.compare(stateCSV) == 0)
                {
                    stateFile.close();
                    return true;
                } 
            }         
        }
        stateFile.close();
        return false;        
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
    string filename = "patient_records.txt";

    do {
        Patient patient;
        patient.inputData();
        FileManager::writeToFile(patient, filename);

        cout << "Do you want to enter another record? (Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');

    return 0;
}
