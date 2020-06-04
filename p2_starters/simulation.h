/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"

// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.
int search_user(const struct User_t user[], const string& user1);
// EFFECTS: Search the username (user1) is in which location of the array of type struct User_t

void print_request(const string& request);
// EFFECTS: Print out request when read in

void follow(struct User_t &user1, struct User_t &user2);
// MODIFIES: struct User_t: user1 (following), user2 (follower)
// EFFECTS: Implement the request: user1 follow user2

void unfollow(struct User_t &user1, struct User_t &user2);
// MODIFIES: struct User_t: user1 (following), user2 (follower)
// EFFECTS: Implement the request: user1 unfollow user2

void like(struct User_t &user1, struct Post_t &post);
// MODIFIES: Post_t post (likes)
// EFFECTS: Implement the request: user1 like user2 post_id

void unlike(struct User_t &user1, struct Post_t &post);
// MODIFIES: Post_t post (likes)
// EFFECTS: Implement the request: user1 unlike user2 post_id

void comment(struct User_t &user1, struct Post_t &post, const string &text);
// MODIFIES: Post_t post (comment)
// EFFECTS: Implement the request: user1 comment user2 post_id \n text

void uncomment(struct User_t &user1, struct Post_t &post, int commend_index);
// MODIFIES: Post_t post(comment)
// EFFECTS: Implement the request: user1 uncomment user2 post_id comment_id

void post(struct User_t &user1, const string new_post_line[]);
// MODIFIES: User_t user1.post
// EFFECTS: Implement the request: user1 post

void unpost(struct User_t &user1, int post_index);
// MODIFIES: User_t user1.post
// EFFECTS: Implement the request: user1 delete post_id

void refresh(struct User_t &user1);
// EFFECTS: Implement the request: user1 refresh

void visit(struct User_t &user1, struct User_t &user2);
// EFFECTS: Implement the request: user1 visit user2

int compare_ASCII (string &l_str, string &r_str);
// EFFECTS: Compare the string l_str, r_str recursively based on the first character
// used for trending function
int compare_tag (struct Tag_t A, struct Tag_t B);
// EFFECTS: compare the
void trending(struct User_t user[], int top_n, struct Tag_t tag_all[]);
// MODIFIES: Tag_t tag_all
// EFFECTS: Implement the request: trending n


/*
void visit(...);
void trending(...);
void refresh(...);
void follow(...);
void unfollow(...);
void like(...);
void unlike(...);
void comment(...);
void uncomment(...);
void post(...);
void unpost(...);
*/

/* Helper Functions */

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);


void printUser_detailed(User_t& user);
// EFFECTS: print detailed information of the user

void printPost_detailed(Post_t& post);

void printPost_all_for_one(User_t& user);
