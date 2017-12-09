/*
 * Copyright © 2015-2017 Samuel Holland <samuel@sholland.org>
 * SPDX-License-Identifier: 0BSD
 * vim: ft=c:noexpandtab:sts=8:sw=8:ts=8:tw=80
 */

#define _GNU_SOURCE     /* unshare() */
#include <fcntl.h>
#include <grp.h>
#include <limits.h>
#include <linux/sched.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/* Enough space for 3 9-digit integers, 2 spaces, a newline, and a null
 * terminator. */
#define BUFFER_MAX 31

void
die(char *msg)
{
	fputs(msg, stderr);
	exit(1);
}

int
main(int argc, char *argv[])
{
	int status;
	pid_t child, parent = getpid();
	uid_t id = 0;

	if (argc < 3)
		die("usage: userns map_base command...\n");

	/* unshare(2) causes us to drop priveleges, so the uid/gid maps have to
	 * be written from another process that has CAP_SETUID and CAP_SETGID in
	 * the *parent* namespace. */
	if ((child = fork()) < 0) {
		die("fork failed\n");
	} else if (!child) {
		char buffer[BUFFER_MAX], filename[PATH_MAX];
		int fd, len;

		/* Wait for the main process to unshare(). */
		raise(SIGSTOP);

		/* Now that the parent is in the new namespace and has woken us
		 * up with SIGCONT, we can give it priveleges. */
		len = snprintf(buffer, BUFFER_MAX, "0 %s 65536\n", argv[1]);

		snprintf(filename, PATH_MAX, "/proc/%u/setgroups", parent);
		if ((fd = open(filename, O_WRONLY)) >= 0) {
			if (write(fd, "allow", 5) < 0)
				die("allow setgroups failed\n");
			close(fd);
		}

		snprintf(filename, PATH_MAX, "/proc/%u/uid_map", parent);
		if ((fd = open(filename, O_WRONLY)) >= 0) {
			if (write(fd, buffer, len) < 0)
				die("write uid_map failed\n");
			close(fd);
		}

		snprintf(filename, PATH_MAX, "/proc/%u/gid_map", parent);
		if ((fd = open(filename, O_WRONLY)) >= 0) {
			if (write(fd, buffer, len) < 0)
				die("write gid_map failed\n");
			close(fd);
		}

		return 0;
	}

	/* Synchronize with the child. It cannot set up mappings until we call
	 * unshare(), but if we call unshare() too fast and send SIGCONT before
	 * the child freezes itself, it will never wake up. */
	waitpid(child, &status, WUNTRACED);

	/* Put ourselves in a new namespace */
	if (unshare(CLONE_NEWUSER | CLONE_NEWNS))
		die("unshare failed\n");

	/* Ask the child to set up mappings in the new namespace. If it exits
	 * successfully, we know we can become root. */
	kill(child, SIGCONT);
	waitpid(child, &status, 0);
	if (!WIFEXITED(status) || WEXITSTATUS(status))
		die("mapping failed\n");

	/* Until now, we are running as the overflow uid/gid with all
	 * capabilities. Set uid and gid to 0 to maintain priveleges after
	 * execvp(). */
	setgroups(1, &id);
	setuid(id);
	setgid(id);

	execvp(argv[2], argv + 2);
	die("execvp failed\n");
}
