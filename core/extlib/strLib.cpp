#include "strLib.h"

int length(const char* s) {
	int count = 0;
	while (s[count] != '\0')
		count++;

	return count;
}

void removeSpace(char* s) {
	int pos = 0;
	int count = 0;
	while (s[count] != '\0') {
		s[pos] = s[count];
		if (s[count] != ' ') pos++;
		count++;
	}
	s[pos] = '\0';
}

double stod(char* s) {
	double temp = 0.0;
	bool flag_point = false;
	long count = 0;
	double multiplier = 10.0;

	while (s[count] != '\0') {
		if (s[count] == '.') {
			flag_point = true; /* If there wasn't a '.' then turn flag on */
			multiplier = 1.0/10.0;
			count++;
			continue;
		}
		if (!flag_point) {
			temp *= multiplier;
			temp += double(s[count] - '0');
		} else {
			temp += (double(s[count] - '0') * multiplier);
			multiplier *= 0.1;
		}
		count++;
	}

	return temp;
}