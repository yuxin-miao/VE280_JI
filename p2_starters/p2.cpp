#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cassert>
#include <algorithm>
#include "server_type.h"
#include "simulation.h"

using namespace std;

// 缩短main！
int main(int argc, char *argv[]) {

    exception_invalid_argument(argc);

    /******USERNAME INITIALIZATION****/
    // READ: User data

    string user_dir;
    User_t user[30];

    ifstream read_username;
    read_username.open(argv[1]);
    int count_user = 0;
    if (read_username.is_open()) {
        getline(read_username, user_dir);
        string user_name;
        for (int i = 0; getline(read_username, user_name); i++) {
            user[i].username = user_name;
            count_user++;
        }
        read_username.close();
    }
    else {
        exception_file_missing(argv[1]);
        return 0;
    }
    if (!exception_capacity_overflow(user)) return 0; // MAX_USER overflow

    // READ: User directories
    ifstream read_user_dir;
    for (int i = 0; i < count_user; i++) {
        string user_info;
        read_user_dir.open( user_dir + "/" + user[i].username + "/" + "user_info");
        stringstream ss_user_info;
        if (read_user_dir.is_open()) {
            while (getline(read_user_dir, user_info)) {
                ss_user_info << user_info << " " ;
            }
            read_user_dir.close();
        }
        else {
            exception_file_missing(user_dir + "/" + user[i].username + "/" + "user_info");
            return 0;
        }
        string temp;
        int user_info_num = 0; // store the digits in stringstream
        int count_info_num = 0;
        while (ss_user_info >> user_info_num) {
            if (count_info_num == 0) {user[i].num_posts = (unsigned int)user_info_num; count_info_num++;}
            else if (count_info_num == 1) {user[i].num_following = (unsigned int)user_info_num; count_info_num++; //store the num_following and the following names
                for (int j = 0; j < user_info_num; j++) {
                    ss_user_info >> temp;
                    for (int search_it = 0; search_it < count_user; search_it++) {
                        if (user[search_it].username == temp) {
                            user[i].following[j] = &user[search_it];
                        }
                    }
                }
            }
            else if (count_info_num == 2) {user[i].num_followers = user_info_num; count_info_num++; //store the num_follower and the follower names
                for (int j = 0; j < user_info_num; j++) {
                    ss_user_info >> temp;
                    for (int search_it = 0; search_it < count_user; search_it++) {
                        if (user[search_it].username == temp) {
                            user[i].follower[j] = &user[search_it];
                        }
                    }
                }
            }

        }
        if (!exception_capacity_overflow(user)) return 0;
        // MAX posts / followings / followers overflow
        if (user[i].num_posts != 0) { //read posts
            for (unsigned int loop_post = 0; loop_post < user[i].num_posts; loop_post++) {
                user[i].posts[loop_post].owner = &user[i];
                stringstream path_post;
                path_post << user_dir << "/" << user[i].username << "/posts/" << loop_post + 1;
                ifstream read_post(path_post.str());
                if (read_post.is_open()) {
                    string post_content;
                    getline(read_post, post_content);
                    user[i].posts[loop_post].title = post_content;

                    int tag_num = 0;
                    while (getline(read_post, post_content)) {
                        if (post_content[0] == '#') {
                            user[i].posts[loop_post].tags[tag_num] = post_content.substr(1, post_content.length() - 2);
                            tag_num++;
                        }
                        if (tag_num > 5) {
                            // Detect number of tags overflow
                            exception_post_overflow(user[i].posts[loop_post]);
                            return 0;
                        }
                        else if (isdigit(post_content[0])) {user[i].posts[loop_post].num_likes = stoi(post_content);
                            break;
                        }
                        else {
                            user[i].posts[loop_post].text = post_content;
                        }
                    }
                    user[i].posts[loop_post].num_tags = tag_num;
                    if (!exception_capacity_overflow_post(user[i].posts[loop_post])) return 0; // Detect number of likes overflow
                    for (unsigned int like_user = 0; like_user < user[i].posts[loop_post].num_likes; like_user++) {
                        getline(read_post, post_content);
                        for (int search_it = 0; search_it < count_user; search_it++) {
                            if (user[search_it].username == post_content) {
                                user[i].posts[loop_post].like_users[like_user] = &user[search_it];
                            }
                        }
                    }
                    getline(read_post, post_content); int num_comment = stoi(post_content);
                    user[i].posts[loop_post].num_comments = (unsigned int)num_comment;
                    if (!exception_capacity_overflow_post(user[i].posts[loop_post])) return 0; // Detect number of comments overflow
                    for (unsigned int comment_num = 0; comment_num < user[i].posts[loop_post].num_comments; comment_num++) {
                        getline(read_post, post_content);
                        for (int search_it = 0; search_it < count_user; search_it++) {
                            if (user[search_it].username == post_content) {
                                user[i].posts[loop_post].comments[comment_num].user = &user[search_it];
                                getline(read_post, post_content);
                                user[i].posts[loop_post].comments[comment_num].text = post_content;
                            }
                        }
                    }
                    read_post.close();
                }
                else {
                    exception_file_missing(path_post.str());
                    return 0;
                }
            }


        }
    }
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

