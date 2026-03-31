#include <stdio.h>

// 將字元 a-f 轉換成對應的位元權值 (1, 2, 4, 8, 16, 32)
int charToBit(char e) {
    if (e < 'a' || e > 'f') return -1;
    return 1 << (e - 'a');
}

int main() {
    int s0, s1;
    char e1_str[10], e2_str[10];
    int error = 0;

    // 讀取輸入
    if (scanf("%d", &s0) != 1) return 0;
    if (scanf("%d", &s1) != 1) return 0;
    scanf("%s", e1_str);
    scanf("%s", e2_str);

    char e1 = e1_str[0];
    char e2 = e2_str[0];

    // 錯誤檢查
    if (s0 < 0 || s0 > 63) { printf("S0 ERROR\n"); error = 1; }
    if (s1 < 0 || s1 > 63) { printf("S1 ERROR\n"); error = 1; }
    if (charToBit(e1) == -1) { printf("e1 ERROR\n"); error = 1; }
    if (charToBit(e2) == -1) { printf("e2 ERROR\n"); error = 1; }

    if (error) return 0;

    // (1) 將 e1 加入 S1 得到 S2
    int s2 = s1 | charToBit(e1);

    // (2) 判斷 e2 是否在 S2 中
    if ((s2 & charToBit(e2)) != 0) printf("Y\n");
    else printf("N\n");

    // (3) 判斷 S2 是否為 S0 的子集合
    if ((s0 & s2) == s2) printf("Y\n");
    else printf("N\n");

    // (4) 交集
    printf("%d\n", s0 & s2);

    // (5) 聯集
    printf("%d\n", s0 | s2);

    // (6) 差集 (S0 - S2)
    // 使用位元與及位元反轉，並限定在 6 位元範圍內
    printf("%d\n", s0 & (~s2));

    return 0;
}