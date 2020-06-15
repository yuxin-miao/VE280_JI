#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "server_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (!exception_invalid_argument(argc)) return 0;

/******USERNAME INITIALIZATION******/
    string user_dir;
    User_t user[30]; // array used to store user information

// READ: username file, if FILE_MISSING, terminate
    if (!read_username_file(argv, user, user_dir)) return 0;

// Detect MAX_USER overflow, if CAPACITY_OVERFLOW, terminate
    if (!exception_capacity_overflow(user)) return 0;

// READ: User directories, other kinds of CAPACITY_OVERFLOW checked
    if (!read_username_dir(user, user_dir)) return 0; // if FILE_MISSING, terminate

/***LOGFILE PROCESSING***/
    string logfile = argv[2];
    if (!logfile_process(user, logfile)) {
        exception_file_missing(logfile); // if FILE_MISSING, terminate
        return 0;
    }
    return 0;
}

