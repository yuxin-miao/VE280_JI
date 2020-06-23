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
    /*
    //int i, dotAns=0;
    list_t listA, listA_answer;
    list_t listB, listC, list_empty;
    list_empty = list_make();
    listA = list_make();
    listB = list_make();
    listC = list_make();
    listA_answer = list_make();

    for(int i = 10; i>0; i--)
    {
        listA = list_make(i, listA);
        listB = list_make(i+10, listB);
        listA = list_make(i, listA);

    }


    for(int j = 10; j > -8; j-=2) {
        listC = list_make(j, listC);
        listC = list_make(j, listC);
        listC = list_make(j, listC);

    }
    //list_print(filter_odd(listC));
    list_print(listC);

    list_print(filter_odd(listC));
    list_print(filter_odd(listC));
    cout << "\n";
    list_print(listA);
    list_print(filter_odd(listA));
    cout << "\n";

    list_print(listB);
    list_print(filter_odd(listB));





    //list_print(filter_odd(listA));
*/

    list_print(list_proper_divisors(12));

}
