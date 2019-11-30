#include <iostream>
#include <algorithm>

#define ITEMS 100
#define WEIGHT 100

#if ITEMS == 2
int value[ITEMS] = {9, 3};
int weight[ITEMS] = {2, 3};
#endif
#if ITEMS == 4
int value[ITEMS] = {9, 3, 5, 7};
int weight[ITEMS] = {2, 3, 3, 1};
#endif
#if ITEMS == 10
int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3};
int weight[ITEMS] = {2, 3, 3, 1, 5, 4, 3, 4, 2, 4};
#endif
#if ITEMS == 20
int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3, 8, 4, 8, 2, 1, 0, 9, 8, 4, 2};
int weight[ITEMS] = {2, 3, 3, 1, 5, 4, 3, 4, 2, 4, 3, 2, 3, 4, 4, 5, 2, 4, 1, 5};
#endif
#if ITEMS == 30
int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3, 8, 4, 8, 2, 1, 0, 9, 8, 4, 2, 5, 6, 7, 1, 1, 0, 1, 5, 1, 4};
int weight[ITEMS] = {2, 3, 3, 1, 5, 4, 3, 4, 2, 4, 3, 2, 3, 4, 4, 5, 2, 4, 1, 5, 2, 5, 3, 3, 5, 4, 5, 4, 1, 2};
#endif
#if ITEMS == 100
int value[ITEMS] = {9, 3, 5, 7, 5, 9, 8, 9, 7, 3, 8, 4, 8, 2, 1, 0, 9, 8, 4, 2, 5, 6, 7, 1, 1, 0, 1, 5, 1, 4, 4, 3, 1, 3, 1, 0, 7, 3, 5, 2, 5, 8, 1, 7, 1, 8, 8, 6, 5, 1, 2, 4, 4, 1, 4, 9, 6, 7, 4, 7, 5, 1, 7, 1, 0, 7, 5, 9, 1, 2, 7, 9, 2, 4, 2, 9, 7, 2, 4, 2, 8, 9, 3, 9, 1, 0, 1, 0, 2, 4, 5, 5, 1, 0, 4, 9, 2, 5, 6, 3};
int weight[ITEMS] = {2, 3, 3, 1, 5, 4, 3, 4, 2, 4, 3, 2, 3, 4, 4, 5, 2, 4, 1, 5, 2, 5, 3, 3, 5, 4, 5, 4, 1, 2, 5, 3, 4, 3, 4, 2, 4, 4, 1, 2, 2, 2, 3, 5, 4, 3, 1, 5, 4, 2, 4, 5, 4, 3, 5, 4, 4, 2, 3, 5, 1, 1, 5, 1, 3, 3, 4, 2, 3, 5, 1, 4, 1, 3, 5, 4, 2, 2, 1, 3, 1, 2, 2, 1, 5, 1, 3, 4, 2, 3, 1, 3, 3, 3, 2, 4, 4, 3, 2, 2};
#endif

int knapsack (int imax, int wmax) {
    int memo[imax+1][wmax+1];
    int i, w;
    for (i = 0; i <= imax; i++) {
        for (w = 0; w <= wmax; w++) {
            if (i == 0 || w == 0) memo[i][w] = 0;
            else if (weight[i-1] > w) memo[i][w] = memo[i-1][w];
            else memo[i][w] = std::max( memo[i-1][w],
                memo[i-1][w-weight[i-1]] + value[i-1]);
        }
    }
    return memo[i-1][w-1];
}

int main () {
    std::cout << knapsack(ITEMS, WEIGHT) << std::endl;
    return 0;
}
