/*
Names: Samuel Ndubuisi and Nivyan Chilumula-Jala 

Date: 2/1/2024

Description: This code provides basic validation for each 
field and writes the patient records to a file using classes
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class Patient {
private:
    string ssn;
    string firstName;
    string lastName;
    char middleInitial;
    string address;
    string city;
    string stateCode;
    string zip;

public:
    // Constructor to initialize patient data
    Patient() : ssn(""), firstName(""), lastName(""), middleInitial('\0'),
                address(""), city(""), stateCode(""), zip("") {}

    // Function to input patient data
    void inputData() {
        cout << "Enter SSN (9 digits): ";
        cin >> ssn;
        // Validate SSN format
        while (ssn.length() != 9 || ssn.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid SSN. Please enter again: ";
            cin >> ssn;
        }

        cout << "Enter first name: ";
        cin >> firstName;
        // Validate first name format
        while (firstName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid name. Please enter again: ";
            cin >> firstName;
        }

        cout << "Enter last name: ";
        cin >> lastName;
        // Validate last name format
        while (lastName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid name. Please enter again: ";
            cin >> lastName;
        }

        cout << "Enter middle initial: ";
        cin >> middleInitial;

        cin.ignore(); // Ignore newline character
        cout << "Enter address: ";
        getline(cin, address);
        // Validate address format
        while (address.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ") != string::npos) {
            cout << "Invalid address. Please enter again: ";
            getline(cin, address);
        }

        cout << "Enter city: ";
        cin >> city;
        // Validate city format
        while (city.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
            cout << "Invalid city. Please enter again: ";
            cin >> city;
        }

        cout << "Enter state code (2 characters): ";
        cin >> stateCode;
        // Validate state code format
        while (stateCode.length() != 2 || !isalpha(stateCode[0]) || !isalpha(stateCode[1])) {
            cout << "Invalid state code. Please enter again: ";
            cin >> stateCode;
        }

        cout << "Enter ZIP code: ";
        cin >> zip;
        // Validate ZIP code format
        while (zip.length() != 5 || zip.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid ZIP code. Please enter again: ";
            cin >> zip;
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
               stateCode + ", " + zip;
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
