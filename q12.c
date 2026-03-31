#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_edge_char(char ch) {
	return (isalpha((unsigned char)ch) || ch == '_');
}

void remove_newline(char *s) {
	char *p = s;
	while (*p != '\0') {
		if (*p == '\n' || *p == '\r') {
			*p = '\0';
			return;
		}
		p++;
	}
}

int validate_string(const char *s) {
	const char *start = s;
	const char *end = s;

	if (*start == '\0') {
		return 0;
	}

	while (*end != '\0') {
		end++;
	}
	end--;

	return is_valid_edge_char(*start) && is_valid_edge_char(*end);
}

void reverse_string(char *s) {
	char *left = s;
	char *right = s;
	char tmp;

	while (*right != '\0') {
		right++;
	}
	right--;

	while (left < right) {
		tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}
}

int length_without_spaces(const char *s) {
	int count = 0;
	const char *p = s;

	while (*p != '\0') {
		if (*p != ' ') {
			count++;
		}
		p++;
	}
	return count;
}

int main() {
	char s1[1005], s2[1005];
	char original1[1005], original2[1005];
	int len1, len2;

	if (fgets(s1, sizeof(s1), stdin) == NULL) {
		return 0;
	}
	if (fgets(s2, sizeof(s2), stdin) == NULL) {
		return 0;
	}

	remove_newline(s1);
	remove_newline(s2);

	if (!validate_string(s1) || !validate_string(s2)) {
		printf("Error\n");
		return 0;
	}

	strcpy(original1, s1);
	strcpy(original2, s2);

	reverse_string(s1);
	reverse_string(s2);

	printf("%s\n", s1);
	printf("%s\n", s2);

	len1 = length_without_spaces(original1);
	len2 = length_without_spaces(original2);

	if (len1 >= len2) {
		printf("%s\n", original1);
	} else {
		printf("%s\n", original2);
	}

	return 0;
}
