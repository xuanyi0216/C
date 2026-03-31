#include <stdio.h>
#include <math.h>

int main() {
    int a, b, c;

    // 依序讀取 a, b, c
    if (scanf("%d %d %d", &a, &b, &c) != 3) return 0;

    // 計算判別式 D = b^2 - 4ac
    double D = (double)b * b - 4.0 * a * c;

    if (D > 0) {
        // 情況一：兩個相異實根
        double x1 = (-b + sqrt(D)) / (2.0 * a);
        double x2 = (-b - sqrt(D)) / (2.0 * a);
        printf("%.1f\n", x1);
        printf("%.1f\n", x2);
    } 
    else if (D == 0) {
        // 情況一：重根 (只輸出一個解)
        double x = (double)(-b) / (2.0 * a);
        // 處理 -0.0 的顯示問題
        if (x == -0.0) x = 0.0;
        printf("%.1f\n", x);
    } 
    else {
        // 情況二：虛根 (D < 0)
        double realPart = (double)(-b) / (2.0 * a);
        double imagPart = sqrt(-D) / (2.0 * a);
        
        // 處理實部為 -0.0 的視覺效果
        if (realPart == -0.0) realPart = 0.0;
        
        // 虛部取絕對值，確保符合 A+Bi, A-Bi 的格式
        if (imagPart < 0) imagPart = -imagPart;

        printf("%.1f+%.1fi\n", realPart, imagPart);
        printf("%.1f-%.1fi\n", realPart, imagPart);
    }

    return 0;
}