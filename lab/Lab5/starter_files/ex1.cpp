#include "ex1.h"

int dot(list_t v1, list_t v2){
	// TODO: implement dot function
	if (list_isEmpty(v1) | list_isEmpty(v2)) return 0;
	else return list_first(v1) * list_first(v2)  + dot(list_rest(v1), list_rest(v2));
}

static list_t reverse_help(list_t list, list_t new_list) {
    static list_t to_return = list_make();
    if (!list_isEmpty(list_rest(list))) {
        new_list = list_make(list_first(list), new_list);
        reverse_help(list_rest(list), new_list);
    }
    else{
        to_return =  list_make(list_first(list), new_list);
    }
    return to_return;
}

static list_t filter_help(list_t list, list_t new_list, bool (*fn)(int)) {
    static list_t to_return = list_make();
    if (list_isEmpty(list)) {

        to_return = new_list;
    }
    else if (fn(list_first(list))) {

        new_list = list_make(list_first(list) , new_list);
        filter_help(list_rest(list), new_list, fn);
    }
    else filter_help(list_rest(list), new_list, fn);
    if (list_isEmpty(to_return)) return to_return;
    else return reverse_help(to_return, list_make());
}

static bool odd(int x) {
    return x % 2 == 1;
}
list_t filter_odd(list_t list){
	// TODO: implement filter_odd function
    return filter(list, odd);
}

list_t filter(list_t list, bool (*fn)(int)){
    if (list_isEmpty(list)) return list;
	// TODO: implement filter function
    return filter_help(list, list_make(), fn);
}

list_t list_proper_divisors(int num){

    list_t result = list_make();
    for (int i = num - 1; i > 0; i--) {
        if (num % i == 0)
            result = list_make(i, result);
    }
    return result;
}

bool is_pseudoperfect_helper(int num, list_t proper_divisors) {
    if (list_isEmpty(proper_divisors)) return num == 0;
    return is_pseudoperfect_helper(num, list_rest(proper_divisors)) ||
           is_pseudoperfect_helper(num - list_first(proper_divisors), list_rest(proper_divisors));
}
bool is_pseudoperfect(int num) {
    list_t proper_divisors = list_proper_divisors(num);
    return is_pseudoperfect_helper(num, proper_divisors);
}