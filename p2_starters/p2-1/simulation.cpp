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

void read_username_file (char* argv[], User_t user[], std::string &user_dir) {
    ifstream read_username;
    read_username.open(argv[1]);
    //int count_user = 0;
    if (read_username.is_open()) {
        getline(read_username, user_dir);
        string user_name;
        for (int i =0; getline(read_username, user_name); i++) {
            user[i].username = user_name;
            //count_user++;
        }
        read_username.close();
    }
    else cout << "Username file open failed!" << endl;
}


int search_user(const struct User_t user[], const string& user1) {
    int index = 0;
    for (int i = 0; !user[i].username.empty(); i++) {
        if (user[i].username == user1) {
            index = i;
            break;
        }
    }
    return index;
}

void print_request(const string& request) {
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
    while (new_post_line[i][0] == '#') {
        user1.posts[user1.num_posts].tags[i-1] = new_post_line[i].substr(1, new_post_line[i].length()-2);
        i++;
    }
    user1.posts[user1.num_posts].num_tags = i - 1;
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
    string temp = left.tag_content;
    unsigned int temp_score = left.tag_score;
    left.tag_score = right.tag_score;
    left.tag_content = right.tag_content;
    right.tag_content = temp;
    right.tag_score = temp_score;
}

int recursive_ASCII (const string& str_left, const string& str_right) {
    if (str_left.empty() | str_right.empty()) return 5;
    if (str_left.at(0) > str_right.at(0)) return 1;
    else if (str_left.at(0) < str_right.at(0))
        return 0;
    else
        return recursive_ASCII(str_left.substr(1), str_right.substr(1));
}

void bubble_sort (struct Tag_t tag_all[], const int tag_num) {
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
    /*cout << "Before sorting..." << endl;
    for (int i = 0; i < top_n && i < tag_num; i++) {
        printTag(tag_all[i], i + 1);
    }*/

    bubble_sort(tag_all, tag_num);
    //cout << "After sorting..." << endl;

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
    return 0;
}

int exception_file_missing(const std::string &file_name) {
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
        oStream << "Maximal number of tag is " << MAX_TAGS << "." << endl;
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
            // Detect number of tags per post overflow
            ostringstream oStream;
            oStream << "Error: Too many likes for post " << post.title << "!" << endl;
            oStream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, oStream.str());
        }
        if(post.num_comments > MAX_COMMENTS){
            // Detect number of tags per post overflow
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