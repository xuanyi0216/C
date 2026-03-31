#include <stdio.h>

int main() {
    int n, m;

    // 使用 scanf 的回傳值來判斷是否為合法整數輸入
    if (scanf("%d %d", &n, &m) != 2) {
        printf("error\n");
        return 0;
    }

    // 範圍檢查
    if (n < 1 || n > 2 || m < 2 || m > 9) {
        printf("error\n");
        return 0;
    }

    if (n == 1) {
        for (int i = 0; i < m; i++) {
            // 1. 輸出前綴井字號
            for (int j = 0; j < m - 1 - i; j++) {
                printf("#");
            }

            // 2. 輸出中間的星號與字母
            // 第一行特殊處理，只有一個星號
            if (i == 0) {
                printf("*");
            } else {
                // 字母計算：第二行(i=1)是A, 第三行(i=2)是B... 
                // 循環為 (i-1)%3 -> 0:A, 1:B, 2:C
                char letter = 'A' + (i - 1) % 3;
                for (int k = 0; k < i; k++) {
                    printf("*%c", letter);
                }
                printf("*"); // 結尾補一個星號
            }

            // 3. 輸出後綴井字號
            for (int j = 0; j < m - 1 - i; j++) {
                printf("#");
            }
            printf("\n");
        }
    } 
    else if (n == 2) {
        for (int i = 1; i <= m; i++) {
            // 1. 左側遞減數字 (i 到 1)
            for (int j = i; j >= 1; j--) {
                printf("%d", j);
            }

            // 2. 中間星號 (M - i + 1) * 2 個
            int stars = (m - i + 1) * 2;
            for (int j = 0; j < stars; j++) {
                printf("*");
            }

            // 3. 右側遞增數字 (1 到 i)
            for (int j = 1; j <= i; j++) {
                printf("%d", j);
            }
            printf("\n");
        }
    }

    return 0;
}