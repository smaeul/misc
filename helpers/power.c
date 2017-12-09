/*
 * Copyright © 2015-2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: 0BSD
 * vim: ft=c:noexpandtab:sts=8:sw=8:ts=8:tw=80
 */

#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char *next, *states, *token;
	FILE *fp = 0;
	size_t len;

	if (!(fp = fopen("/sys/power/state", "r+")))
		goto err;

	if (argc != 2) {
		printf("usage: %s <state>\n", argv[0]);
		goto invalid;
	}

	if ((len = getline(&states, &len, fp)) < 1)
		goto err;
	if (!(token = strtok_r(states, " \n", &next)))
		goto err;
	while (strcmp(token, argv[1]))
		if (!(token = strtok_r(0, " \n", &next)))
			goto invalid;
	if (fprintf(fp, "%s", token) < (int)strlen(token))
		goto err;

	return 0;

err:
	if (fp)
		fclose(fp);
	perror(argv[0]);
	return 111;

invalid:
	if (fp && !fseek(fp, 0, SEEK_SET) && getline(&states, &len, fp) >= 1)
		printf("valid states: %s", states);
	return 100;
}
