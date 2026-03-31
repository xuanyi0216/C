#include <stdio.h>
#include <string.h>

// 函式：將牌面轉換為點數
float getPoint(char card[]) {
    if (strcmp(card, "A") == 0) return 1.0;
    if (strcmp(card, "J") == 0 || strcmp(card, "Q") == 0 || strcmp(card, "K") == 0) return 0.5;
    if (strcmp(card, "10") == 0) return 10.0;
    
    // 處理 2-9 的情況，將字元轉為數字
    return (float)(card[0] - '0');
}

int main() {
    char input[5];
    float scoreX = 0, scoreY = 0;

    // 讀取玩家 X 的三張牌
    for (int i = 0; i < 3; i++) {
        scanf("%s", input);
        scoreX += getPoint(input);
    }

    // 讀取玩家 Y 的三張牌
    for (int i = 0; i < 3; i++) {
        scanf("%s", input);
        scoreY += getPoint(input);
    }

    // 爆牌判斷 (超過 10.5 變為 0)
    if (scoreX > 10.5) scoreX = 0;
    if (scoreY > 10.5) scoreY = 0;

    // 輸出 X 與 Y 的總點數 (%g 會自動處理小數點後的零)
    printf("%g\n", scoreX);
    printf("%g\n", scoreY);

    // 判斷勝負
    if (scoreX > scoreY) {
        printf("X Win\n");
    } else if (scoreY > scoreX) {
        printf("Y Win\n");
    } else {
        printf("Tie\n");
    }

    return 0;
}