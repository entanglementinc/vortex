#include <iostream>

int value[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
int weight1 = 76;
int weight2 = 81;
int weight3 = 0;

bool subset_sum (int imax, int wmax) {
    bool memo[imax+1][wmax+1];
    int i, w;
    for (i = 0; i <= imax; i++) {
        for (w = 0; w <= wmax; w++) {
            if (w == 0) memo[i][w] = true;
            else if (i == 0) memo[i][w] = false;
            else if (value[i-1] > w) memo[i][w] = memo[i-1][w];
            else memo[i][w] = memo[i-1][w] || memo[i-1][w-value[i-1]];
        }
    }
    return memo[i-1][w-1];
}

int main() {
    std::cout << subset_sum(10, weight1) << std::endl; // should return true
    std::cout << subset_sum(10, weight2) << std::endl; // should return false
    std::cout << subset_sum(10, weight3) << std::endl; // 0 always true
    return 0;
}
