#include <stdio.h>

int team_index(char team) {
	if (team == 'A') return 0;
	if (team == 'B') return 1;
	return 2;
}

int main(void) {
	int m;
	int win_count[3] = {0, 0, 0};
	int total_score[3] = {0, 0, 0};

	if (scanf("%d", &m) != 1) {
		return 0;
	}

	for (int game = 0; game < m; game++) {
		char t1, t2;
		int sum1 = 0, sum2 = 0;

		scanf(" %c %c", &t1, &t2);

		for (int quarter = 0; quarter < 4; quarter++) {
			int s1, s2;
			scanf("%d %d", &s1, &s2);
			sum1 += s1;
			sum2 += s2;
		}

		total_score[team_index(t1)] += sum1;
		total_score[team_index(t2)] += sum2;

		if (sum1 > sum2) {
			int idx = team_index(t1);
			win_count[idx]++;
		} else {
			int idx = team_index(t2);
			win_count[idx]++;
		}
	}

	int best = 0;
	for (int i = 1; i < 3; i++) {
		if (win_count[i] > win_count[best]) {
			best = i;
		}
	}

	printf("%c %d\n", (char)('A' + best), total_score[best]);
	return 0;
}
