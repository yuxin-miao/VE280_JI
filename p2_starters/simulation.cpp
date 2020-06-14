/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */
#include "simulation.h"
#include "server_type.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

/***INITIALIZATION***/
int read_username_file (char* argv[], User_t user[], std::string &user_dir) { //read username file (argv[1]))
    ifstream read_username;
    read_username.open(argv[1]);
    if (read_username.is_open()) {
        getline(read_username, user_dir);
        string user_name;
        for (int i =0; getline(read_username, user_name); i++) {
            user[i].username = user_name;
        }
        read_username.close();
    }
    else {
        exception_file_missing(argv[1]);
        return 0;
    }
    return 1;
}

int read_username_dir (User_t user[], const std::string &user_dir) {
    ifstream read_user_dir;
    // read user_info
    for (int i = 0; !user[i].username.empty(); i++) {
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
        unsigned int user_info_num = 0; // store the digits in stringstream
        unsigned int count_info_num = 0;
        while (ss_user_info >> user_info_num) {
            if (count_info_num == 0) {
                user[i].num_posts = user_info_num;
                count_info_num++;
            }
            else if (count_info_num == 1) {
                user[i].num_following = user_info_num;
                count_info_num++; //store the num_following and the following names
                if (!exception_capacity_overflow(user)) return 0;
                for (unsigned int j = 0; j < user_info_num; j++) {
                    ss_user_info >> temp;
                    int user_index = search_user(user, temp);
                    user[i].following[j] = &user[user_index];
                }
            }
            else if (count_info_num == 2) {
                user[i].num_followers = user_info_num;
                count_info_num++; //store the num_follower and the follower names
                if (!exception_capacity_overflow(user)) return 0;
                for (unsigned int j = 0; j < user_info_num; j++) {
                    ss_user_info >> temp;
                    int user_index = search_user(user, temp);
                    user[i].follower[j] = &user[user_index];
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
                            bool exist = false; // whether a repetitive tag
                            for (int tag_in = 0; !user[i].posts[loop_post].tags[tag_in].empty(); tag_in++) {
                                if (user[i].posts[loop_post].tags[tag_in] == post_content.substr(1, post_content.length() - 2)) {
                                    exist = true;
                                    break;
                                }
                            }
                            if ((tag_num < 5) & (!exist)) {
                                user[i].posts[loop_post].tags[tag_num]
                                = post_content.substr(1,post_content.length() - 2);
                                tag_num++;
                            }
                            else if ((tag_num == 5) & (!exist)) {
                                tag_num++;
                            }
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
                        int user_index = search_user(user, post_content);
                        user[i].posts[loop_post].like_users[like_user] = &user[user_index];
                    }
                    getline(read_post, post_content); int num_comment = stoi(post_content);
                    user[i].posts[loop_post].num_comments = (unsigned int)num_comment;
                    if (!exception_capacity_overflow_post(user[i].posts[loop_post])) return 0; // Detect number of comments overflow
                    for (unsigned int comment_num = 0; comment_num < user[i].posts[loop_post].num_comments; comment_num++) {
                        getline(read_post, post_content);
                        int user_index = search_user(user, post_content);
                        user[i].posts[loop_post].comments[comment_num].user = &user[user_index];
                        getline(read_post, post_content);
                        user[i].posts[loop_post].comments[comment_num].text = post_content;
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
    return 1;
}


int logfile_process(User_t user[], const std::string& logfile) {
    // logfile processing, read in request
    ifstream read_logfile;
    read_logfile.open(logfile);
    string request_line;
    Tag_t tag_all[5001];
    if (read_logfile.is_open()) {
        while (getline(read_logfile, request_line)) {
            stringstream request_ss;
            request_ss << request_line;
            string user1, request, user2;
            int user1_index, user2_index; // for the corresponding user's index in array user[]
            unsigned int post_id;
            request_ss >> user1;
            if (user1 == "trending") { // as the only request that do not have user.username
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
    else return 0; // check FILE_MISSING exception
    return 1;
}


int search_user(const struct User_t user[], const string& user1) {
    // search user index in array user[]
    int index = 0;
    for (int i = 0; !user[i].username.empty(); i++) {
        if (user[i].username == user1) {
            index = i;
            break;
        }
    }
    return index;
}

void print_request(const string& request) { // print out the request
    cout << ">> " << request << endl;
}

// TODO: Define your functions in this header file.
void follow(struct User_t &user1, struct User_t &user2){
    user1.following[user1.num_following] = &user2;
    user1.num_following++;
    user2.follower[user2.num_followers] = &user1;
    user2.num_followers++;
}

void unfollow(struct User_t &user1, struct User_t &user2) {
    // find the followers's index
    for (unsigned int i = 0; i < user1.num_following; i++) {
        if (user1.following[i]->username == user2.username) {
            for (unsigned int j = i; j < user1.num_following - 1; j++) {
                user1.following[j] = user1.following[j + 1];
            }
            break;
        }
    }
    user1.num_following--;
    user1.following[user1.num_following] = nullptr;
    // move the other followers forward
    for (unsigned int i = 0; i < user2.num_followers; i++) {
        if (user2.follower[i]->username == user1.username) {
            for (unsigned int j = i; j < user2.num_followers - 1; j++) {
                user2.follower[j] = user2.follower[j + 1];
            }
            break;
        }
    }
    user2.num_followers--;
    user2.follower[user2.num_followers] = nullptr;
}

void like(struct User_t &user1, struct Post_t &post) {
    post.like_users[post.num_likes] = &user1;
    post.num_likes++;
}

void unlike(struct User_t &user1, struct Post_t &post) {
    for (unsigned int i = 0; i < post.num_likes; i++) {
        if (post.like_users[i]->username == user1.username) {
            for (unsigned int j = i; j < post.num_likes - 1; j++) {
                post.like_users[j] = post.like_users[j+1];
            }
            break;
        }
    }
    post.num_likes--;
    post.like_users[post.num_likes] = nullptr;
}

void comment(struct User_t &user1, struct Post_t &post, const string &text) {
    post.comments[post.num_comments].text = text;
    post.comments[post.num_comments].user = &user1;
    post.num_comments++;
}

void uncomment(struct Post_t &post, const int commend_index) {
    for (unsigned int i = commend_index; i < post.num_comments-1; i++) {
        post.comments[i].user = post.comments[i+1].user;
        post.comments[i].text = post.comments[i+1].text;
    }
    post.num_comments--;
    post.comments[post.num_comments].user = nullptr;
    post.comments[post.num_comments].text = "";
}

void post(struct User_t &user1, const string new_post_line[]) {

    user1.posts[user1.num_posts].owner = &user1;
    user1.posts[user1.num_posts].title = new_post_line[0];
    int i = 1;
    int tag_num = 0;
    // read in tags, deal with repetitive tags
    while (new_post_line[i][0] == '#') {
        bool exist = false;
        for (int tag_in = 0; !user1.posts[user1.num_posts].tags[tag_in].empty(); tag_in++) {
            if (user1.posts[user1.num_posts].tags[tag_in] == new_post_line[i].substr(1, new_post_line[i].length()-2)) {
                exist = true;
                break;
            }
        }
        if (!exist && i < 5) {
            user1.posts[user1.num_posts].tags[tag_num] = new_post_line[i].substr(1, new_post_line[i].length()-2);
            tag_num++;
        }
        i++;
    }
    user1.posts[user1.num_posts].num_tags = tag_num;
    user1.posts[user1.num_posts].text = new_post_line[i];
    user1.posts[user1.num_posts].num_comments = 0;
    user1.posts[user1.num_posts].num_likes = 0;
    user1.num_posts++;
}

void unpost(struct User_t &user1, const int post_index) {
    for (unsigned int i = post_index; i < user1.num_posts - 1; i++) {
        user1.posts[i] = user1.posts[i+1];
    }
    user1.posts[user1.num_posts].owner = nullptr;
    user1.num_posts--;
}

void refresh(struct User_t &user1) {
    for (unsigned int i = 0; i < user1.num_posts; i++) {
        printPost(user1.posts[i]);
    }
    for (unsigned int i = 0; i < user1.num_following; i++) {
        for (unsigned int j = 0; j < user1.following[i]->num_posts; j++) {
            printPost(user1.following[i]->posts[j]);
        }
    }
}

void visit(struct User_t &user1, struct User_t &user2) {
    string relationship;
    // first for one refresh himself
    if (&user1 == &user2) {
        printUser(user2, "");
        return;
    }
    bool user1_fo_user2 = false;
    bool user2_fo_user1 = false;
    for (unsigned int i = 0; i < user1.num_following; i++) {
        if (user1.following[i] == &user2) {
            user1_fo_user2 = true;
            break;
        }
    }
    for (unsigned int i = 0; i < user2.num_following; i++) {
        if (user2.following[i] == &user1) {
            user2_fo_user1 = true;
            break;
        }
    }
    if (user1_fo_user2 & user2_fo_user1) relationship = "friend";
    else if (user1_fo_user2 & !user2_fo_user1) relationship = "following";
    else if (!user1_fo_user2) relationship = "stranger";
    printUser(user2, relationship);
}

void bubble_sort_swap (struct Tag_t& left, struct Tag_t& right) {
    // swap the two struct
    string temp = left.tag_content;
    unsigned int temp_score = left.tag_score;
    left.tag_score = right.tag_score;
    left.tag_content = right.tag_content;
    right.tag_content = temp;
    right.tag_score = temp_score;
}

int recursive_ASCII (const string& str_left, const string& str_right) {
    // recursively compare the two string
    if (str_left.empty() | str_right.empty()) return 5;
    if (str_left.at(0) > str_right.at(0)) return 1;
    else if (str_left.at(0) < str_right.at(0))
        return 0;
    else
        return recursive_ASCII(str_left.substr(1), str_right.substr(1));
}

void bubble_sort (struct Tag_t tag_all[], const int tag_num) {
    // using bubble sort to sort the array tag_all[]
    for (int i = 0; i < tag_num - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < tag_num - i - 1; j++) {
            if (tag_all[j].tag_score < tag_all[j + 1].tag_score)
            {bubble_sort_swap(tag_all[j], tag_all[j + 1]); swapped = true;}
            else if (tag_all[j].tag_score == tag_all[j + 1].tag_score) {
                int ASCII = recursive_ASCII(tag_all[j].tag_content, tag_all[j + 1].tag_content);
                if (ASCII == 1)
                {bubble_sort_swap(tag_all[j], tag_all[j + 1]); swapped = true;}
                else if (ASCII == 5){
                    if (tag_all[j].tag_content.length() > tag_all[j + 1].tag_content.length())
                    {bubble_sort_swap(tag_all[j], tag_all[j + 1]); swapped = true;}
                }
            }
        }
        if (!swapped) break;
    }

}

void trending(struct User_t user[], int top_n, struct Tag_t tag_all[]) {
    // first delete the tag_score stored
    for (int i = 0; !tag_all[i].tag_content.empty(); i++) {
        tag_all[i].tag_score = 0;
    }

    // for every post's tag, calculate the score
    for (int i = 0; !user[i].username.empty(); i++) {
        for (unsigned int post_index = 0; post_index < user[i].num_posts; post_index++) {
            for (unsigned int tag_index = 0; tag_index < user[i].posts[post_index].num_tags; tag_index++) {
                int tag_in_array = 0;
                for (; !tag_all[tag_in_array].tag_content.empty(); tag_in_array++) {
                    if (user[i].posts[post_index].tags[tag_index] == tag_all[tag_in_array].tag_content) {
                        // this tag exists in the array of tag
                        tag_all[tag_in_array].tag_score = tag_all[tag_in_array].tag_score + 5
                                                          + 3 * user[i].posts[post_index].num_comments + user[i].posts[post_index].num_likes;
                        break;
                    }
                }
                if (tag_all[tag_in_array].tag_content.empty()) {
                    tag_all[tag_in_array].tag_score = 0;
                    // this tag does not exist in the array of tag
                    // add this new tag to array
                    tag_all[tag_in_array].tag_content = user[i].posts[post_index].tags[tag_index];
                    tag_all[tag_in_array].tag_score = tag_all[tag_in_array].tag_score + 5
                                                      + 3 * user[i].posts[post_index].num_comments + user[i].posts[post_index].num_likes;
                }
            }
        }
    }
    int tag_num = 0;
    do {tag_num++;} while (!tag_all[tag_num].tag_content.empty());


    bubble_sort(tag_all, tag_num);

    for (int i = 0; i < top_n && i < tag_num; i++) {
        printTag(tag_all[i], i + 1);
    }
}

/* Helper Functions */

// Printing

void printUser(User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post){
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}

/***EXCEPTION***/
int exception_invalid_argument(int argc) {
    try{
        if(argc < 3){
            ostringstream oStream;
            oStream << "Error: Wrong number of arguments!" << endl;
            oStream << "Usage: ./p2 <username> <logfile>" << endl;
            throw Exception_t(INVALID_ARGUMENT, oStream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_file_missing(const std::string &file_name) {
    // for file_missing, throw the exception
    try{
        ostringstream ostream;
        ostream << "Error: Cannot open file " << file_name << "!" <<endl;
        throw Exception_t(FILE_MISSING, ostream.str());
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
}

int exception_capacity_overflow(const User_t user[]) {
    try {
        // Detect user number overflow
        unsigned int num_user = 0;
        do { num_user++; } while (!user[num_user].username.empty());
        if (num_user > MAX_USERS) {
            ostringstream ostream;
            ostream << "Error: Too many users!" << endl;
            ostream << "Maximal number of users is " << MAX_USERS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, ostream.str());
        }

        for (unsigned int i = 0; i < num_user; i++) {
            if (user[i].num_posts > MAX_POSTS) {
                // Detect posts number per user overflow
                ostringstream ostream;
                ostream << "Error: Too many posts for user " << user[i].username << "!" << endl;
                ostream << "Maximal number of posts is " << MAX_POSTS << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, ostream.str());

            }
            if (user[i].num_following > MAX_FOLLOWING) {
                // Detect number of following per user overflow
                ostringstream ostream;
                ostream << "Error: Too many followings for user " << user[i].username << "!" << endl;
                ostream << "Maximal number of followings is " << MAX_FOLLOWING << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, ostream.str());
            }
            if (user[i].num_followers > MAX_FOLLOWERS) {
                // Detect number of following per user overflow
                ostringstream ostream;
                ostream << "Error: Too many followers for user " << user[i].username << "!" << endl;
                ostream << "Maximal number of followers is " << MAX_FOLLOWERS << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, ostream.str());
            }
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_post_overflow(const Post_t &post) {
    try{// Detect number of tags per post overflow
        ostringstream oStream;
        oStream << "Error: Too many tags for post " << post.title << "!" << endl;
        oStream << "Maximal number of tags is " << MAX_TAGS << "." << endl;
        throw Exception_t(CAPACITY_OVERFLOW, oStream.str());

    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
}

int exception_capacity_overflow_post(const Post_t &post) {
    try{
        if(post.num_likes > MAX_LIKES){
            // Detect number of likes per post overflow
            ostringstream oStream;
            oStream << "Error: Too many likes for post " << post.title << "!" << endl;
            oStream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
        if(post.num_comments > MAX_COMMENTS){
            // Detect number of comments per post overflow
            ostringstream oStream;
            oStream << "Error: Too many comments for post " << post.title << "!" << endl;
            oStream << "Maximal number of comments is " << MAX_COMMENTS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }

    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_like(const User_t &user1, const User_t &user2, const unsigned int post_id) {
    try{
        if (user2.num_posts < post_id || post_id < 1) {
            // Check whether user2 has post post_id
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot like post #" << post_id << " of " << user2.username << "!" << endl;
            oStream << user2.username << " does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            for (unsigned int i = 0; i < user2.posts[post_id-1].num_likes; i++) {
                if (user2.posts[post_id-1].like_users[i]->username == user1.username) {
                    ostringstream oStream;
                    oStream << "Error: " << user1.username << " cannot like post #" << post_id << " of " << user2.username << "!" << endl;
                    oStream << user1.username << " has already liked post #" << post_id << " of " << user2.username << "." << endl;
                    throw Exception_t(INVALID_LOG, oStream.str());
                }
            }
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_unlike(const User_t &user1, const User_t &user2, const unsigned int post_id) {
    try{
        if (user2.num_posts < post_id || post_id < 1) {
            // Check whether user2 has post post_id
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot unlike post #" << post_id
                    << " of " << user2.username << "!" << endl;
            oStream << user2.username << " does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else {
            bool liked = false;
            for (unsigned int i = 0; i < user2.posts[post_id-1].num_likes; i++) {
                if (user2.posts[post_id-1].like_users[i]->username == user1.username) {
                    liked = true;
                    break;
                }
            }
            if (!liked) {
                // do not have post
                ostringstream oStream;
                oStream << "Error: " << user1.username << " cannot unlike post #" << post_id
                        << " of " << user2.username << "!" << endl;
                oStream << user1.username << " has not liked post #" << post_id << " of " << user2.username << "." << endl;
                throw Exception_t(INVALID_LOG, oStream.str());
            }
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_comment(const User_t &user1, const User_t &user2, const unsigned int post_id) {
    try {
        if (user2.num_posts < post_id || post_id < 1) {
            // Check whether user2 has post post_id
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot comment post #" << post_id
                    << " of " << user2.username<< "!" << endl;
            oStream << user2.username << " does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_uncomment(const User_t &user1, const User_t &user2, const unsigned int post_id, const unsigned int comment_id) {
    try {
        if (user2.num_posts < post_id || post_id < 1) {
            // Check whether user2 has post post_id
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot uncomment comment #" << comment_id
                    << " of post #" << post_id
                    << " posted by " << user2.username<< "!" << endl;
            oStream << user2.username << " does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else if (user2.posts[post_id-1].num_comments < comment_id || comment_id < 1) {
            // Check whether user2's #post_id has comment #comment_id
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot uncomment comment #" << comment_id
                    << " of post #" << post_id
                    << " posted by " << user2.username<< "!" << endl;
            oStream << "Post #" << post_id << " does not have comment #" << comment_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
        else if (user2.posts[post_id-1].comments[comment_id-1].user->username != user1.username) {
            // Check whether user2's #post_id's comment #comment_id belongs to user1
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot uncomment comment #" << comment_id
                    << " of post #" << post_id
                    << " posted by " << user2.username<< "!" << endl;
            oStream <<  user1.username << " is not the owner of comment #" << comment_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}

int exception_delete(const User_t &user1, const unsigned int post_id) {
    try {
        if (user1.num_posts < post_id || post_id < 1) {
            // Check whether user1 has post post_id
            ostringstream oStream;
            oStream << "Error: " << user1.username << " cannot delete post #" << post_id << "!" << endl;
            oStream << user1.username << " does not have post #" << post_id << "." << endl;
            throw Exception_t(INVALID_LOG, oStream.str());
        }
    }
    catch (Exception_t &exception) {
        cout << exception.error_info;
        return 0;
    }
    return 1;
}