/*
 * Copyright © 2015-2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: 0BSD
 * vim: ft=c:noexpandtab:sts=8:sw=8:ts=8:tw=80
 */

#include <stdio.h>
#include <sys/prctl.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage: %s <program>\n", argv[0]);
		return 100;
	}

	if (prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0))
		goto err;
	if (execvp(argv[1], argv + 1))
		goto err;

	/* UNREACHABLE */

err:
	perror(argv[0]);
	return 111;
}
