#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// 檢查是否為合法整數（供內部邏輯使用，包含前導零與長度判斷開關）
int is_pure_integer(char *s, int check_leading_zero, int min_len, int max_len) {
    int len = strlen(s);
    if (len < min_len || len > max_len) return 0;
    int start = 0;
    if (s[0] == '-') {
        if (len == 1) return 0; // 只有負號
        start = 1;
    }
    // 前導零檢查：如果長度大於1且第一位是0，且不是 "-0" 或 "0"
    if (check_leading_zero && s[start] == '0' && len - start > 1) return 0;
    
    for (int i = start; i < len; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

// 變數判斷
int is_variable(char *s) {
    int len = strlen(s);
    if (len < 1 || len > 10) return 0;
    if (!isalpha(s[0]) && s[0] != '_') return 0;
    for (int i = 1; i < len; i++) {
        if (!isalnum(s[i]) && s[i] != '_') return 0;
    }
    return 1;
}

// 浮點數判斷
int is_float(char *s) {
    int len = strlen(s);
    if (len < 3 || len > 50) return 0;
    int start = 0;
    if (s[0] == '-') start = 1;
    
    char *dot = strchr(s + start, '.');
    if (!dot || strchr(dot + 1, '.') || dot == s + start || dot == s + len - 1) return 0;

    // 檢查整數部分前導零
    int int_part_len = dot - (s + start);
    if (int_part_len > 1 && s[start] == '0') return 0;

    for (int i = start; i < len; i++) {
        if (s[i] != '.' && !isdigit(s[i])) return 0;
    }
    return 1;
}

// 分數判斷 (回傳 1:真, 2:假, 0:否)
int check_fraction(char *s) {
    int len = strlen(s);
    if (len < 1 || len > 10) return 0;
    char temp[51]; strcpy(temp, s);
    char *slash = strchr(temp, '/');
    if (!slash || slash == temp || slash == temp + len - 1) return 0;

    *slash = '\0';
    char *num_str = temp;
    char *den_str = slash + 1;

    // 分子分母必須是整數，且分母不能有負號，且分母不能為0
    if (!is_pure_integer(num_str, 1, 1, 10)) return 0;
    // 分母規則：不可有負號，不可前導零，不可為0
    if (den_str[0] == '-' || !is_pure_integer(den_str, 1, 1, 10) || strcmp(den_str, "0") == 0) return 0;

    long long num = atoll(num_str);
    long long den = atoll(den_str);
    if (num < 0) num = -num;
    if (den < 0) den = -den;
    if (num == 0) return 0; // 分子不可為 0

    return (num < den) ? 1 : 2;
}

int is_mixed_fraction(char *s) {
    int len = strlen(s);
    if (len < 1 || len > 10) return 0;
    char *space = strchr(s, ' ');
    if (!space) return 0;

    char part1[51], part2[51];
    int space_idx = space - s;
    strncpy(part1, s, space_idx); part1[space_idx] = '\0';
    strcpy(part2, space + 1);

    // 前半部是整數，後半部是真分數，且整數不能為0
    if (is_pure_integer(part1, 1, 1, 10) && strcmp(part1, "0") != 0 && strcmp(part1, "-0") != 0) {
        if (check_fraction(part2) == 1) return 1;
    }
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    getchar(); // 跳過換行

    while (n--) {
        char s[100];
        if (!fgets(s, sizeof(s), stdin)) break;
        s[strcspn(s, "\r\n")] = 0; // 移除換行符

        if (is_pure_integer(s, 1, 1, 50)) printf("integer\n");
        else if (is_mixed_fraction(s)) printf("mixed fraction\n");
        else {
            int frac = check_fraction(s);
            if (frac == 1) printf("proper fraction\n");
            else if (frac == 2) printf("improper fraction\n");
            else if (is_float(s)) printf("float\n");
            else if (is_variable(s)) printf("variable\n");
            else printf("string\n");
        }
    }
    return 0;
}