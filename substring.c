#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcre.h"

char* substring(char*, int, int);

int main() {
	const char *error;
	int erroffset;
	pcre *re;
	int rc;
	int ovector[100];

	char *regex = "^\\/([a-z0-9]+)\\/phpmyadmin/";
	char str[] = "/abc12345/phpmyadmin/stlackflow";

	re = pcre_compile(regex, /* the pattern */
			PCRE_MULTILINE,
			&error, /* for error message */
			&erroffset, /* for error offset */
			0); /* use default character tables */
	if (!re) {
		printf("pcre_compile failed (offset: %d), %s\n", erroffset, error);
		return -1;
	}

	char *token[10];

	unsigned int offset = 0;
	unsigned int len = strlen(str);

	printf("\n\n");

	while (offset < len && (rc = pcre_exec(re, 0, str, len, offset, 0, ovector, sizeof (ovector))) >= 0) {
		for (int i = 0; i < rc; ++i) {
			printf("position %d, length %d -> %s\n", ovector[2 * i], ovector[2 * i + 1] - ovector[2 * i], str);
			token[i] = substring(str, ovector[2 * i], ovector[2 * i + 1] - ovector[2 * i]);
			printf("value to store in array -> %.*s\n", ovector[2 * i + 1] - ovector[2 * i], str + ovector[2 * i]);
		}
		offset = ovector[1];
	}

	printf("\n\n");

	printf("first index of array -> %s \n", token[0]);
	printf("second index of array -> %s \n", token[1]);

	printf("\n\n");

	return 1;
}

/*C substring function: It returns a pointer to the substring */

char *substring(char *string, int position, int length) {
	char *pointer;
	int c;
	pointer = (char *) malloc(length + 1);
	if (pointer == NULL) {
		printf("Unable to allocate memory.\n");
		exit(1);
	}

	for (c = 0; c < length - position; c++)
		*(pointer + c) = string[position + c];
	*(pointer + c) = '\0';

	return pointer;
}