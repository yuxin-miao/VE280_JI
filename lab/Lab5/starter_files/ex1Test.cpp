#include <iostream>
#include "recursive.h"
#include "ex1.h"

using namespace std;
/*
static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    
*/
int main()
{
    int i, dotAns=0;
    list_t listA, listA_answer;
    list_t listB, listC;

    listA = list_make();
    listB = list_make();
    listC = list_make();
    listA_answer = list_make();

    for(i = 5; i>0; i--)
    {
        listA = list_make(i, listA);
        listB = list_make(i+10, listB);
        dotAns += i*(i+10);
    }

    for(i = 5; i>0; i-=2)
    {
        listA_answer = list_make(i, listA_answer);
    }
    for(int j = 3; j > 0; j--) {
        listC = list_make(j, listC);
    }
    //list_print(filter_odd(listC));
    list_print(filter_odd(listA));
    list_print(filter_odd(listC));
    //list_print(filter_odd(listA));


}
