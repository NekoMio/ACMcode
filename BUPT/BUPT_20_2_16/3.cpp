#include <bits/stdc++.h>
using namespace std;
int main() {
    int a1 = 5, a2 = 5, a3 = 5;
    while (1) {
        bool flag = 0;
        while (a2 >= 4) {
            flag = 1;
            a2 -= 3, a3 += 1, a1++;
        }
        while (a3 >= 2) {
            flag = 1;
            a3--, a2++, a1++;
        }
        if (!flag) break;
    }
    printf ("%d %d %d\n", a1, a2, a3);
    while (1);
}

// 5
// 5
// 5

// 6
// 2
// 6

// 9
// 5
// 3

// 10
// 2
// 4

// 12
// 4
// 2

// 13
// 1
// 3

// 14
// 2
// 2

// 15
// 3
// 1

