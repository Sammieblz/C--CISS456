#include <iostream>
#include <sqlite3.h>
#include <chrono>
#include <ctime>

// Function to get current date and time as a string
std::string getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_c);
}

// Function to check if a patient exists in the database
bool isPatientExists(sqlite3 *db, const std::string& ssn) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM PATIENTS WHERE SSN = ?";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, ssn.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    } else {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

// Function to check if an ICD-10 code exists in the database
bool isICD10Exists(sqlite3 *db, const std::string& icd10) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM ICD10 WHERE ICD10CODE = ?";
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, icd10.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return count > 0;
    } else {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
}

// Function to handle encounter logic
void handleEncounter(sqlite3 *db, const std::string& ssn, const std::string& icd10) {
    // Check if patient exists
    if (!isPatientExists(db, ssn)) {
        std::cout << "Patient with SSN " << ssn << " does not exist in the database." << std::endl;
        return;
    }

    // Check if ICD-10 code exists
    if (!isICD10Exists(db, icd10)) {
        std::cout << "ICD-10 code " << icd10 << " does not exist in the database." << std::endl;
        return;
    }

    // Get current date and time
    std::string encounterDate = getCurrentDateTime();

    // Prepare SQL statement
    const char *sql = "INSERT INTO Encounter (SSN, Date, ICD10CODE) VALUES (?, ?, ?)";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Bind parameters
    sqlite3_bind_text(stmt, 1, ssn.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, encounterDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, icd10.c_str(), -1, SQLITE_STATIC);

    // Execute statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to insert record: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "New encounter record inserted successfully." << std::endl;
    }

    // Finalize statement
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("A3_DB.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Get user input for SSN and ICD-10 code
    std::string ssn, icd10;
    std::cout << "Enter patient SSN: ";
    std::cin >> ssn;
    std::cout << "Enter ICD-10 code: ";
    std::cin >> icd10;

    // Handle encounter with user input
    handleEncounter(db, ssn, icd10);
    
    sqlite3_close(db);
    return 0;
}