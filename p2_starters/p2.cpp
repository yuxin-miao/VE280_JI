#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "server_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[]) {
    exception_invalid_argument(argc);

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
    ifstream read_logfile;
    read_logfile.open(argv[2]);
    string request_line;
    Tag_t tag_all[5001];
    if (read_logfile.is_open()) {
        while (getline(read_logfile, request_line)) {
            stringstream request_ss;
            request_ss << request_line;
            string user1, request, user2;
            int user1_index, user2_index;
            unsigned int post_id;
            request_ss >> user1;
            if (user1 == "trending") {
                print_request(user1);
                int top_n;
                request_ss >> top_n;
                trending(user, top_n, tag_all);
            }
            request_ss >> request;
            if (request == "follow") {
                print_request(request);
                request_ss >> user2;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                follow(user[user1_index], user[user2_index]);
            }
            else if (request == "unfollow") {
                print_request(request);
                request_ss >> user2;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                unfollow(user[user1_index], user[user2_index]);
            }
            else if (request == "like") {
                print_request(request);
                request_ss >> user2 >> post_id;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                if (exception_like(user[user1_index], user[user2_index], post_id))
                    like(user[user1_index], user[user2_index].posts[(int)post_id-1]);
            }
            else if (request == "unlike") {
                print_request(request);
                request_ss >> user2 >> post_id;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                if (exception_unlike(user[user1_index], user[user2_index], post_id))
                    unlike(user[user1_index], user[user2_index].posts[(int)post_id-1]);
            }
            else if (request == "comment") {
                print_request(request);
                request_ss >> user2 >> post_id;
                string text;
                getline(read_logfile, text);
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                if (exception_comment(user[user1_index], user[user2_index], post_id))
                    comment(user[user1_index], user[user2_index].posts[(int)post_id-1], text);
            }
            else if (request == "uncomment") {
                print_request(request);
                unsigned int comment_id;
                request_ss >> user2 >> post_id >> comment_id;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                if (exception_uncomment(user[user1_index], user[user2_index], post_id, comment_id))
                    uncomment(user[user2_index].posts[post_id-1], (int)comment_id - 1);
            }
            else if (request == "post") {
                string new_post_line[10];
                print_request(request);
                getline(read_logfile, new_post_line[0]);
                int i = 1;
                while (getline(read_logfile, new_post_line[i])) {
                    if (new_post_line[i][0] != '#') break;
                    i++;
                }
                user1_index = search_user(user, user1);
                post(user[user1_index], new_post_line);
            }
            else if (request == "delete") {
                print_request(request);
                request_ss >> post_id;
                user1_index = search_user(user, user1);
                if (exception_delete(user[user1_index], post_id))
                    unpost(user[user1_index], (int)post_id - 1);
            }
            else if (request == "refresh") {
                print_request(request);
                user1_index = search_user(user, user1);
                refresh(user[user1_index]);
            }
            else if (request == "visit") {
                print_request(request);
                request_ss >> user2;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                visit(user[user1_index], user[user2_index]);
            }
        }
        read_logfile.close();
    }
    else cout << "LOGFILE OPEN FAILED!" << endl;
    return 0;
}

