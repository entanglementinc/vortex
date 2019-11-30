#include <iostream>

// #define ITEMS 30
// #define WEIGHT 75
//
// #if ITEMS == 2
// int value[ITEMS] = {9, 3};
// #endif
// #if ITEMS == 4
// int value[ITEMS] = {9, 3, 5, 7};
// #endif
// #if ITEMS == 10
// int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3};
// #endif
// #if ITEMS == 20
// int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3, 8, 4, 8, 2, 1, 0, 9, 8, 4, 2};
// #endif
// #if ITEMS == 30
// int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3, 8, 4, 8, 2, 1, 0, 9, 8, 4, 2, 5, 6, 7, 1, 1, 0, 1, 5, 1, 4};
// #endif
// #if ITEMS == 100
// int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3, 8, 4, 8, 2, 1, 0, 9, 8, 4, 2, 5, 6, 7, 1, 1, 0, 1, 5, 1, 4, 4, 3, 1, 3, 1, 0, 7, 3, 5, 2, 5, 8, 1, 7, 1, 8, 8, 6, 5, 1, 2, 4, 4, 1, 4, 9, 6, 7, 4, 7, 5, 1, 7, 1, 0, 7, 5, 9, 1, 2, 7, 9, 2, 4, 2, 9, 7, 2, 4, 2, 8, 9, 3, 9, 1, 0, 1, 0, 2, 4, 5, 5, 1, 0, 4, 9, 2, 5, 6, 3};
// #endif

int value[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
int weight1 = 76;
int weight2 = 81;
int weight3 = 0;

bool subset_sum(int i, int acc, int w) {
    if (i <= 0) return false;
    if (acc == w) return true;

    int new_acc = acc + value[i-1];

    if (new_acc > w) return subset_sum(i-1, acc, w);

    bool s1 = subset_sum(i-1, new_acc, w);
    bool s2 = subset_sum(i-1, acc, w);

    if (s1 || s2) return true;
    else return false;
}

int main() {
    std::cout << subset_sum(10, 0, weight1) << std::endl; // should return true
    std::cout << subset_sum(10, 0, weight2) << std::endl; // should return false
    std::cout << subset_sum(10, 0, weight3) << std::endl; // 0 always true
    return 0;
}
