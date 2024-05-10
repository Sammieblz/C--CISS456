#include <iostream>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open Database
    rc = sqlite3_open("chinook.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return(1);
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // SQL Query to Select State Codes
    const char *sql = "SELECT StateCodes FROM states;";

    // Execute SQL Query
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Operation done successfully" << std::endl;
    }

    // Close Database
    sqlite3_close(db);

    return 0;
}
