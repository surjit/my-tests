#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcre.h"

char* substring(const char* str, size_t begin, size_t len);
char *get_token(char *regex, char *str);

int main() {

	char *regex = "^\\/([a-z0-9]+)\\/phpmyadmin/";
	char *str = "/YYabc1234500/phpmyadmin/stlackflow";

	char *token = get_token(regex, str);
	if (NULL == token) {
		printf("Not Match \n");
	} else {
		printf("%s \n", token);
	}

	return 1;
}

/*C substring function: It returns a pointer to the substring */
char *get_token(char *regex, char *str) {
	char *token;
	const char *error;
	int erroffset;
	pcre *re;
	int rc;
	int ovector[100];

	re = pcre_compile(regex, /* the pattern */
			PCRE_MULTILINE,
			&error, /* for error message */
			&erroffset, /* for error offset */
			0); /* use default character tables */
	if (!re) {
		printf("pcre_compile failed (offset: %d), %s\n", erroffset, error);
		return NULL;
	}

	unsigned int offset = 0;
	unsigned int len = strlen(str);

	int position, length;

	while (offset < len && (rc = pcre_exec(re, 0, str, len, offset, 0, ovector, sizeof (ovector))) >= 0) {
		for (int i = 0; i < rc; ++i) {
			if (i == 0 || i > 1)
				continue;
			position = ovector[2 * i];
			length = ovector[2 * i + 1] - ovector[2 * i];
		}
		offset = ovector[1];
	}

	token = substring(str, position, length);
	return token;
}

char* substring(const char* str, size_t begin, size_t len) {
	if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin + len))
		return 0;

	return strndup(str + begin, len);
}