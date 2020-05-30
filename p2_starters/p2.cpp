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

using namespace std;
void read_username_file (const string& name);
int main(int argc, char *argv[]) {
    // READ: User data - username file
    ifstream read_username;
    read_username.open(argv[1]);
    string user_dir;
    User_t user[30]; // 确定一下有没有说最多几个user
    int count_user = 0;
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
        //stringstream path;
        //path << "./" << user_dir << "/" << user[i].username << "/" << "user_info";
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
        if (user[i].num_posts != 0) {
            //read posts
            for (int loop_post = 0; loop_post < user[i].num_posts; loop_post++) {
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

                    }

                    read_post.close();
                }
                else cout << "OPEN POST FAILED!" << endl;
            }


        }
    }


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
    return 0;
}

void read_username_file (const string& name) {
    // MODIFIES:
    // READ: User data - username file
    ifstream read_username;
    read_username.open(name);
    string user_dir;
    User_t user[30]; // 确定一下有没有说最多几个user
    int count_user = 0;
    if (read_username.is_open()) {
        getline(read_username, user_dir);
        string user_name;
        for (int i =0; getline(read_username, user_name); i++) {
            user[i].username = user_name;
            count_user++;
        }
        read_username.close();
    }

}
