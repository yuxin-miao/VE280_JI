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
void read_username_file (const string& name);
int main(int argc, char *argv[]) {
    /******USERNAME INITIALIZATION****/
    // READ: User data
    ifstream read_username;
    read_username.open(argv[1]);
    string user_dir;
    User_t user[30]; // 确定一下有没有说最多几个user
    //Post_t posts_all[1001];
    int count_user = 0;
    //int count_post = 0;
    if (read_username.is_open()) {
        getline(read_username, user_dir);
        string user_name;
        for (int i =0; getline(read_username, user_name); i++) {
            user[i].username = user_name;
            count_user++;
        }
        read_username.close();
    }

    // READ: User directories
    ifstream read_user_dir;
    for (int i = 0; i < count_user; i++) {
        string user_info;
        read_user_dir.open("./" + user_dir + "/" + user[i].username + "/" + "user_info");
        stringstream ss_user_info;
        if (read_user_dir.is_open()) {
            while (getline(read_user_dir, user_info)) {
                ss_user_info << user_info << " " ;
            }
            read_user_dir.close();
        }
        else cout << "User directories do not open!" << endl;
        string temp;
        int user_info_num = 0; // store the digits in stringstream
        int count_info_num = 0;
        while (ss_user_info >> user_info_num) {
            if (count_info_num == 0) {user[i].num_posts = user_info_num; count_info_num++;}
            else if (count_info_num == 1) {user[i].num_following = user_info_num; count_info_num++; //store the num_following and the following names
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
        if (user[i].num_posts != 0) { //read posts
            for (int loop_post = 0; loop_post < user[i].num_posts; loop_post++) {
                user[i].posts[loop_post].owner = &user[i];
                stringstream path_post;
                path_post << "./" << user_dir << "/" << user[i].username << "/posts/" << loop_post + 1;
                ifstream read_post(path_post.str());
                if (read_post.is_open()) {
                    string post_content;
                    getline(read_post, post_content);
                    user[i].posts[loop_post].title = post_content;
                    int tag_num = 0;
                    while (getline(read_post, post_content)) {
                        if (post_content[0] == '#') {
                            user[i].posts[loop_post].tags[tag_num] = post_content;
                            tag_num++;
                        }
                        else if (isdigit(post_content[0])) {user[i].posts[loop_post].num_likes = stoi(post_content);
                            break;
                        }
                        else {
                            user[i].posts[loop_post].text = post_content;
                        }
                    }
                    user[i].posts[loop_post].num_tags = tag_num;
                    for (int like_user = 0; like_user < user[i].posts[loop_post].num_likes; like_user++) {
                        getline(read_post, post_content);
                        for (int search_it = 0; search_it < count_user; search_it++) {
                            if (user[search_it].username == post_content) {
                                user[i].posts[loop_post].like_users[like_user] = &user[search_it];
                            }
                        }
                    }
                    getline(read_post, post_content); int num_comment = stoi(post_content);
                    user[i].posts[loop_post].num_comments = num_comment;
                    for (int comment_num = 0; comment_num < user[i].posts[loop_post].num_comments; comment_num++) {
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
                else cout << "OPEN POST FAILED!" << endl;
                //posts_all[count_post] = user[i].posts[loop_post];
                //posts_all[count_post].owner = &user[i];
                //count_post++;
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
            int post_id;
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
                like(user[user1_index], user[user2_index].posts[post_id-1]);
            }
            else if (request == "unlike") {
                print_request(request);
                request_ss >> user2 >> post_id;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                unlike(user[user1_index], user[user2_index].posts[post_id-1]);
            }
            else if (request == "comment") {
                print_request(request);
                request_ss >> user2 >> post_id;
                string text;
                getline(read_logfile, text);
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                comment(user[user1_index], user[user2_index].posts[post_id-1], text);
            }
            else if (request == "uncomment") {
                print_request(request);
                int comment_id;
                request_ss >> user2 >> post_id >> comment_id;
                user1_index = search_user(user, user1);
                user2_index = search_user(user, user2);
                uncomment(user[user1_index], user[user2_index].posts[post_id-1], comment_id - 1);
            }
            else if (request == "post") {
                print_request(request);
                stringstream post_ss;
                getline(read_logfile, request_line);
                post_ss << request_line << " ";
                while (getline(read_logfile, request_line)) {
                    if (request_line[0] == '#') post_ss << request_line << " ";
                    else break;
                }
                post_ss << request_line << " ";
                user1_index = search_user(user, user1);
                post(user[user1_index], &post_ss);
            }
            else if (request == "delete") {
                print_request(request);
                request_ss >> post_id;
                user1_index = search_user(user, user1);
                unpost(user[user1_index], post_id - 1);
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

            /*for (int i = 0; getline(read_username, user_name); i++) {
                user[i].username = user_name;
                count_user++;
            }*/
        }
        read_logfile.close();
    }
    else cout << "LOGFILE OPEN FAILED!" << endl;


    /*
     * TEST

    int test_num = 7;
    cout << "TEST: " << user[test_num].username << endl;
    cout << "POSTS: " << user[test_num].num_posts << endl;
    cout << "NUM_FOLLOWing: " << user[test_num].num_following << endl;
    for (int i = 0; i < user[test_num].num_following; i++) {
        cout << user[test_num].following[i]->username << endl;
    }
    cout << "NUM_FOLLOWers: " << user[test_num].num_followers << endl;
    for (int i = 0; i < user[test_num].num_followers; i++) {
        cout << user[test_num].follower[i]->username << endl;
    }*/

    /*TEST WITH DEFAULT FUNCTION*/
    //cout << posts_all[0].owner->username << endl;
    //cout << user[0].posts[0].owner->username << endl;
    //printUser(user[0], "follower");
    //cout << user[0].follower[0]->num_followers << endl;
    //printPost(user[0].posts[0]);
    //cout << user[0].posts[0].title << endl;
    return 0;
}

