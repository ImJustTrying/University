#include "Change.h"

void Change::getChange(float chng) {
    int coins[] = { 1, 5, 10, 25, 50 };
    auto* count = new int[SIZE];
    int maxCoin = SIZE - 1;

    for (int i = 0; i < SIZE; i++) {
        count[i] = 0;
    }

    while (chng > 0) {
        if (chng < coins[maxCoin]) {
            --maxCoin;
        }
        else {
            chng -= coins[maxCoin];
            count[maxCoin]++;
        }
    }
    change_count = count;
    delete(count);
}
