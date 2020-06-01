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

void search_user();
void follow(struct User_t *user1, struct User_t *user2);
// MODIFIES: The array user[] of struct User_t type
// EFFECTS: Implement the request: user1 follows user2

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

