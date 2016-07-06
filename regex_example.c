#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pcre.h"

int mainpp() {
	const char *error;
	int erroffset;
	pcre *re;
	int rc;
	int i;
	int ovector[100];

	char *regex = "^\\/([a-z0-9]+)\\/phpmyadmin/";
	char str[] = "/dfsf544/phpmyadmin/fgdgfgf55";

	re = pcre_compile(regex, /* the pattern */
			PCRE_FIRSTLINE,
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
	while (offset < len && (rc = pcre_exec(re, 0, str, len, offset, 0, ovector, sizeof (ovector))) >= 0) {
		for (int i = 0; i < rc; ++i) {
			printf("%2d: %.*s\n", i, ovector[2 * i + 1] - ovector[2 * i], str + ovector[2 * i]);
			printf("\n\n");
		}
		offset = ovector[1];
	}

	//char *tsr = token[1];
	//printf("%s ss", tsr);

	return 1;
}