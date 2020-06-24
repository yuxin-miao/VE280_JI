
#include "recursive.h"

bool containSublistHelper(list_t list, list_t sub) {
    if (list_isEmpty(sub)) return true;
    if (list_isEmpty(list)) return false;
    if (list_first(list) == list_first(sub)) {
        return containSublistHelper(list_rest(list), list_rest(sub));
    } else {
        return false;
    }
}

bool containSublist(list_t list, list_t sub) {
    // EFFECTS: returns true if list contains sub, and false otherwise
    list_t new_list = list;
    bool to_determine = false;
    while (!list_isEmpty(new_list)) {
        to_determine = containSublistHelper(new_list, sub);
        if (to_determine) break;
        new_list = list_rest(new_list);
    }
    return to_determine;
}

