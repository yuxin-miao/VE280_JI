//
// Created by Zhuoer Zhu on 10/06/2020.
//

#ifndef LAB5_EX1_H
#define LAB5_EX1_H

#include "recursive.h"

int dot(list_t v1, list_t v2);
/* 
// REQUIRES: Both "v1" and "v2" are non-empty
//
// EFFECTS: Treats both lists as vectors. Returns the dot
//          product of the two vectors. If one list is longer
//          than the other, ignore the longer part of the vector.
*/



list_t filter(list_t list, bool (*fn)(int));
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
//          For example, if predicate bool odd(int a) returns true
//          if a is odd, then the function filter(list, odd) has
//          the same behavior as the function filter_odd(list).
*/

list_t filter_odd(list_t list);
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value, 
//          in the order in which they appeared in list.
//
//          For example, if you apply filter_odd to the list
//          ( 3 4 1 5 6 ), you would get the list ( 3 1 5 ).
*/
list_t list_proper_divisors(int num);
// REQUIRES: "num" is a positive integer
// EFFECTS: returns a list_t which contains all the proper
// divisors of "num" in ascending order

bool is_pseudoperfect(int num);
// REQUIRES: "num" is a positive integer
// EFFECTS: returns true if "num" is a pseudoperfect number,
// false otherwise
bool is_pseudoperfect_helper(int num, list_t proper_divisors);
// REQUIRES: TODO
// EFFECTS: TODO
#endif