#include <stdio.h>

int main() {
    int w, h;
    
    // 讀取輸入
    if (scanf("%d %d", &w, &h) != 2) return 0;

    // (1) 範圍檢查
    if (w < 20 || w > 100 || h < 100 || h > 200) {
        printf("ERROR\n");
        return 0;
    }

    // (2) 計算 BMI
    double heightMeter = h / 100.0;
    double bmiRaw = w / (heightMeter * heightMeter);

    // (3) 實作「四捨六入五看偶」到整數
    int integerPart = (int)bmiRaw;
    // 取出小數點後第一位 (例如 20.55 -> 5)
    int firstDecimal = (int)(bmiRaw * 10) % 10;
    int bmiFinal;

    if (firstDecimal <= 4) {
        bmiFinal = integerPart;
    } else if (firstDecimal >= 6) {
        bmiFinal = integerPart + 1;
    } else { // firstDecimal == 5
        if (integerPart % 2 != 0) {
            // 整數是奇數 -> 捨去
            bmiFinal = integerPart;
        } else {
            // 整數非奇數(偶數) -> 進位
            bmiFinal = integerPart + 1;
        }
    }

    // (4) 輸出結果
    printf("%d\n", bmiFinal);

    if (bmiFinal < 18) {
        printf("too low\n");
    } else if (bmiFinal > 24) {
        printf("too high\n");
    }

    return 0;
}