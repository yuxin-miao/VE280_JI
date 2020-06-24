
int main() {


/*** Simple input***/
    list_t listA = list_make();
    list_t listB = list_make();
    list_t listC = list_make();
    list_t result1 = list_make();
    list_t result2 = list_make();
    list_t result3 = list_make();
    // generate list for test
    for (int i = 100; i > 90; i--) {
        listA = list_make(i, listA);
        listB = list_make(i - 3, listB);
        listC = list_make(i - 6, listC);
    }
    // generate correct result
    for (int i = 97; i > 90; i--) {
        result1 = list_make(i, result1);
        result2 = list_make(i - 3, result2);
    }
    for (int i = 94; i > 90; i--) {
        result3 = list_make(i, result3);
    }

    assert(list_equal(result1, symmetricDifference(listA, listB)));
    assert(list_equal(result2, symmetricDifference(listB, listC)));
    assert(list_equal(result3, symmetricDifference(listA, listC)));

/*** boundary cases***/
    list_t listD = list_make();
    list_t listE = list_make();
    list_t listF = list_make();
    list_t listG = list_make();

    list_t result4 = list_make();
    list_t result5 = list_make();
    list_t result6 = list_make();
    // generate list for test
    for (int i = 55; i > 50; i--) {
        listD = list_make(i, listD);
        listE = list_make(i - 5, listE);
        listF = list_make(i - 4, listF);
        listG = list_make(i + 4 , listG);

    }
    // generate correct result
    result5 = list_make(51, result5);
    result6 = list_make(55, result6);

    //When the two do not have same number
    assert(list_equal(result4, symmetricDifference(listD, listE)));
    //When the two have one same number, which is the smallest for listD
    assert(list_equal(result5, symmetricDifference(listD, listF)));
    //When the two have one same number, which is the largest for listD
    assert(list_equal(result6, symmetricDifference(listD, listG)));


/***non-sense cases ***/



    try {
        int x = 0;
        if (!list_equal(result1, symmetricDifference(listA, listB)) ||
                !list_equal(result2, symmetricDifference(listB, listC)) ||
                !list_equal(result3, symmetricDifference(listA, listC)))
            throw x;
    }

    catch (int) {
        std::cout << "Wrong in simple" << std::endl;
    }






}

