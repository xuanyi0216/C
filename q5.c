#include <stdio.h>

// 定義資費結構，方便管理數據
typedef struct {
    int plan_name;       // 方案名稱 (183, 383, 983)
    int monthly_fee;     // 月租費
    int free_voice_in;   // 免費網內秒數
    int free_voice_out;  // 免費網外秒數
    int free_landline;   // 免費市話秒數
    int free_sms_in;     // 免費網內簡訊
    int free_sms_out;    // 免費網外簡訊
    double rate_voice_in;   // 網內費率
    double rate_voice_out;  // 網外費率
    double rate_landline;   // 市話費率
    double rate_sms_in;     // 網內簡訊費率
    double rate_sms_out;    // 網外簡訊費率
} Plan;

int main() {
    // 初始化三個方案的數據
    Plan plans[3] = {
        {183, 183, 500, 400, 300, 10, 15, 0.08, 0.1393, 0.1349, 1.1287, 1.4803},
        {383, 383, 600, 500, 400, 20, 25, 0.07, 0.1304, 0.1217, 1.1127, 1.2458},
        {983, 983, 700, 600, 500, 30, 35, 0.06, 0.1087, 0.1018, 0.9572, 1.1243}
    };

    int v_in, v_out, land, s_in, s_out;
    
    // 讀取輸入：網內語音、網外語音、市話、網內簡訊、網外簡訊
    if (scanf("%d %d %d %d %d", &v_in, &v_out, &land, &s_in, &s_out) != 5) return 0;

    int best_price = -1;
    int best_plan_name = -1;

    for (int i = 0; i < 3; i++) {
        double total_communication = 0;

        // 計算各項超出額度的費用
        if (v_in > plans[i].free_voice_in)
            total_communication += (v_in - plans[i].free_voice_in) * plans[i].rate_voice_in;
        
        if (v_out > plans[i].free_voice_out)
            total_communication += (v_out - plans[i].free_voice_out) * plans[i].rate_voice_out;
            
        if (land > plans[i].free_landline)
            total_communication += (land - plans[i].free_landline) * plans[i].rate_landline;
            
        if (s_in > plans[i].free_sms_in)
            total_communication += (s_in - plans[i].free_sms_in) * plans[i].rate_sms_in;
            
        if (s_out > plans[i].free_sms_out)
            total_communication += (s_out - plans[i].free_sms_out) * plans[i].rate_sms_out;

        // 規則：總費用 = max(月租費, 總通信費)
        int final_cost = (int)total_communication;
        if (total_communication < plans[i].monthly_fee) {
            final_cost = plans[i].monthly_fee;
        } else {
            // 這裡直接強制轉型 int 即為無條件捨去
            final_cost = (int)total_communication;
        }

        // 比較並記錄最小費用
        // 如果費用相同，題目通常暗示選擇較低月租或按順序，此處依 183 -> 383 -> 983 順序判斷
        if (best_price == -1 || final_cost < best_price) {
            best_price = final_cost;
            best_plan_name = plans[i].plan_name;
        }
    }

    // 輸出結果
    printf("%d\n", best_price);
    printf("%d\n", best_plan_name);

    return 0;
}