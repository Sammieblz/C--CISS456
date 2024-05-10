/*
Names: Samuel Ndubuisi and Nivyan Chilumula-Jala 

Date: 2/1/2024

Description: This code provides basic validation for each 
field and writes the patient records to a file using functions
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Struct for patient demographic record
struct Patient {
    string ssn;
    string firstName;
    string lastName;
    char middleInitial;
    string address;
    string city;
    string stateCode;
    string zip;
};

// Function to validate SSN (for simplicity, assuming SSN length is 9 digits)
bool validateSSN(const string& ssn) {
    return ssn.length() == 9 && ssn.find_first_not_of("0123456789") == string::npos;
}

// Function to validate name (alpha characters only)
bool validateName(const string& name) {
    return name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

// Function to validate address (alphanumeric characters only)
bool validateAddress(const string& address) {
    // Allowing alphanumeric characters, space, and comma for address
    return address.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ,") == string::npos;
}

// Function to validate city (alpha characters only)
bool validateCity(const string& city) {
    return city.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}

// Function to validate state code (assuming state codes are 2 characters)
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

// Function to validate ZIP (digits only)
bool validateZIP(const string& zip) {
    return zip.find_first_not_of("0123456789") == string::npos;
}

// Function to get input from user and populate a patient record
Patient getPatientData() {
    Patient patient;
    cout << "Enter SSN (9 digits): ";
    cin >> patient.ssn;
    while (!validateSSN(patient.ssn)) {
        cout << "Invalid SSN. Please enter again: ";
        cin >> patient.ssn;
    }
    cout << "Enter first name: ";
    cin >> patient.firstName;
    while (!validateName(patient.firstName)) {
        cout << "Invalid name. Please enter again: ";
        cin >> patient.firstName;
    }
    cout << "Enter last name: ";
    cin >> patient.lastName;
    while (!validateName(patient.lastName)) {
        cout << "Invalid name. Please enter again: ";
        cin >> patient.lastName;
    }
    cout << "Enter middle initial: ";
    cin >> patient.middleInitial;
    cin.ignore(); // Ignore newline character
    cout << "Enter address: ";
    getline(cin, patient.address);
    while (!validateAddress(patient.address)) {
        cout << "Invalid address. Please enter again: ";
        getline(cin, patient.address);
    }
    cout << "Enter city: ";
    cin >> patient.city;
    while (!validateCity(patient.city)) {
        cout << "Invalid city. Please enter again: ";
        cin >> patient.city;
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
    }
    cout << "Enter ZIP code: ";
    cin >> patient.zip;
    while (!validateZIP(patient.zip)) {
        cout << "Invalid ZIP code. Please enter again: ";
        cin >> patient.zip;
    }
    return patient;
};

// Function to write patient record to file
void writeToFile(const Patient& patient, const string& filename) {
    ofstream outFile(filename, ios::app);
    if (outFile.is_open()) {
        outFile << patient.ssn << ", " << patient.firstName << ", " << patient.lastName << ", " 
                << patient.middleInitial << ", " << patient.address << ", " << patient.city << ", " 
                << patient.stateCode << ", " << patient.zip << '\n';
        outFile.close();
        cout << "Record written to file successfully.\n";
    } else {
        cout << "Unable to open file.\n";
    }
}

int main() {
    string filename = "patient_records.txt";
    char choice;
    do {
        Patient patient = getPatientData();
        writeToFile(patient, filename);
        cout << "Do you want to enter another record? (Y/N): ";
        cin >> choice;
    } while (toupper(choice) == 'Y');
    return 0;
}
