#include <iostream>
#include <sqlite3.h>

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

    // Close Database
    sqlite3_close(db);

    return 0;
}