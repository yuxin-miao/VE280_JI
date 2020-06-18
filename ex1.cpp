#include "ex1.h"

int dot(list_t v1, list_t v2){
    // TODO: implement dot function
    list_print(v1);
    list_print(v2);
    return 0;

}

list_t filter_odd(list_t list){
    // TODO: implement filter_odd function
    list_print(list);
    return list;
}

list_t filter(list_t list, bool (*fn)(int)){
    list_print(list);
    return list;

}

