/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */
#include "simulation.h"
#include <iostream>
using namespace std;

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

// TODO: Define your functions in this header file.
void follow(struct User_t *user1, struct User_t *user2){
    user1->num_following++;
    user1->following[user1->num_following] = user2;
    user2->num_followers++;
    user2->follower[user2->num_followers] = user1;

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
