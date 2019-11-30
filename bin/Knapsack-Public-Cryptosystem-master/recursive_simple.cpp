#include <iostream>

#define ITEMS 30
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

int knapsack(int i, int* acc_w, int acc_v, int w) {
    if (i <= 0) return acc_v;

    int new_acc_w = (*acc_w) + weight[i-1];
    int new_acc_v = acc_v + value[i-1];

    int s1 = knapsack(i-1, &new_acc_w, new_acc_v, w);
    int s2 = knapsack(i-1, acc_w, acc_v, w);

    if (new_acc_w > w) return s2;

    if (s1 > s2) {
        (*acc_w) = new_acc_w;
        return s1;
    }
    else return s2;
}

int knapsack_better(int i, int acc_w, int acc_v, int w) {
    if (i <= 0) return acc_v;

    int new_acc_w = acc_w + weight[i-1];
    int new_acc_v = acc_v + value[i-1];

    if (new_acc_w > w) return knapsack_better(i-1, acc_w, acc_v, w);

    int s1 = knapsack_better(i-1, new_acc_w, new_acc_v, w);
    int s2 = knapsack_better(i-1, acc_w, acc_v, w);

    if (s1 > s2) return s1;
    else return s2;
}

int main() {
    int acc_w = 0;
    std::cout << knapsack(ITEMS, &acc_w, 0, WEIGHT) << std::endl;
    //std::cout << knapsack_better(ITEMS, 0, 0, WEIGHT) << std::endl;
    return 0;
}
