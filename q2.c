#include <stdio.h>

int main() {
    int hit;
    int score = 0;
    int outs = 0;
    int bases[4] = {0, 0, 0, 0}; // bases[1]=一壘, [2]=二壘, [3]=三壘

    // 依序處理三位打者
    for (int i = 0; i < 3; i++) {
        if (scanf("%d", &hit) != 1) break;

        if (hit == 0) {
            // 情況：出局
            outs++;
            if (outs % 3 == 0) {
                // 每滿三次出局，壘包清空
                bases[1] = 0;
                bases[2] = 0;
                bases[3] = 0;
            }
        } else {
            // 情況：安打 (1, 2, 3, 4)
            // 1. 先處理原先在壘上的跑員
            for (int b = 3; b >= 1; b--) {
                if (bases[b] == 1) {
                    if (b + hit >= 4) {
                        score++;      // 回到本壘得分
                        bases[b] = 0; // 離開原壘包
                    } else {
                        bases[b + hit] = 1; // 移動到新壘包
                        bases[b] = 0;       // 離開原壘包
                    }
                }
            }

            // 2. 處理打者自己
            if (hit >= 4) {
                score++; // 全壘打直接得分
            } else {
                bases[hit] = 1; // 停在對應壘包
            }
        }
    }

    // 輸出總得分
    printf("%d\n", score);
    // 輸出壘包情況 (一、二、三壘)
    printf("%d %d %d\n", bases[1], bases[2], bases[3]);

    return 0;
}