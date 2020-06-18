/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server_type.h"

// TODO: Declare your functions in this header file.


/***INITIALIZATION***/
// MODIFIES: user[], user_dir
// EFFECTS: read file username (argv[1]) and store user directory and user names
int read_username_file (char* argv[], User_t user[], std::string &user_dir);

// MODIFIES: user[]
// EFFECTS: read user directories
int read_username_dir (User_t user[], const std::string &user_dir);

// EFFECTS: Search the username (user1) is in which location of the array of type struct User_t
int search_user(const struct User_t user[], const std::string& user1) ;


/***LOGFILE PROCESSING***/
// EFFECTS: Read the logfile, process
int logfile_process(User_t user[], const std::string& logfile);

// EFFECTS: Print out request when read in
void print_request(const std::string& request);

// MODIFIES: struct User_t: user1 (following), user2 (follower)
// EFFECTS: Implement the request: user1 follow user2
void follow(struct User_t &user1, struct User_t &user2);

// MODIFIES: struct User_t: user1 (following), user2 (follower)
// EFFECTS: Implement the request: user1 unfollow user2
void unfollow(struct User_t &user1, struct User_t &user2);

// MODIFIES: Post_t post (likes)
// EFFECTS: Implement the request: user1 like user2 post_id
void like(struct User_t &user1, struct Post_t &post);

// MODIFIES: Post_t post (likes)
// EFFECTS: Implement the request: user1 unlike user2 post_id
void unlike(User_t &user1, Post_t &post);

// MODIFIES: Post_t post (comment)
// EFFECTS: Implement the request: user1 comment user2 post_id \n text
void comment(User_t &user1, Post_t &post, const std::string &text);

// MODIFIES: Post_t post(comment)
// EFFECTS: Implement the request: user1 uncomment user2 post_id comment_id
void uncomment(Post_t &post, int commend_index);

// MODIFIES: User_t user1.post
// EFFECTS: Implement the request: user1 post
void post(User_t &user1, const std::string new_post_line[]);

// MODIFIES: User_t user1.post
// EFFECTS: Implement the request: user1 delete post_id
void unpost(User_t &user1, int post_index);

// EFFECTS: Implement the request: user1 refresh
void refresh(User_t &user1);

// EFFECTS: Implement the request: user1 visit user2
void visit(User_t &user1, User_t &user2);

// EFFECTS: Compare the string str_left, str_right recursively based on the first character
// used for trending function
int recursive_ASCII (const std::string& str_left, const std::string& str_right);
// EFFECTS: For trending function, sort the tag based on the score
void bubble_sort (Tag_t tag_all[], int tag_num);
// EFFECTS: For bubble sort, swap Tag_t left and Tag_t right
void bubble_sort_swap (Tag_t& left, Tag_t& right);
// MODIFIES: Tag_t tag_all
// EFFECTS: Implement the request: trending n
void trending(User_t user[], int top_n, Tag_t tag_all[]);



/* Helper Functions */

// Printing
void printUser(User_t& user, const std::string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);


/***EXCEPTION***/
// Initialization error
int exception_invalid_argument(int argc);
// EFFECTS: check whether the number of arguments is less than 2

int exception_file_missing(const std::string &file_name);
// EFFECTS: check whether files are opened successfully

int exception_capacity_overflow(const User_t user[]);
// EFFECTS: check capacity overflow for user number/ posts, followings, followers per user

int exception_post_overflow(const Post_t &post);
// EFFECTS: check capacity overflow for number of tags per post

int exception_capacity_overflow_post(const Post_t &post);
// EFFECTS: check capacity overflow for number of likes/comments per post

// Processing Error
int exception_like(const User_t &user1, const User_t &user2, unsigned int post_id);
// EFFECTS: check invalid log for like request - post_id not exist / already like

int exception_unlike(const User_t &user1, const User_t &user2, unsigned int post_id);
// EFFECTS: check invalid log for unlike request - post_id not exist / not liked

int exception_comment(const User_t &user1, const User_t &user2, unsigned int post_id);
// EFFECTS: check invalid log for comment request - post_id not exist

int exception_uncomment(const User_t &user1, const User_t &user2, int unsigned post_id, int unsigned comment_id);
// EFFECTS: check invalid log for uncomment request -
// post_id not exist / comment_id not exist / comment_id not belong to user1

int exception_delete(const User_t &user1, unsigned int post_id);
// EFFECTS: check invalid log for delete request - post_id not exist





