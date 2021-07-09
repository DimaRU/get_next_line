//
//  main.c
//  get_next_line
//
//  Created by Dmitriy Borovikov on 26.06.2021.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char *argv[]) {
	char *line;
	int file_descriptor;

	setbuf(stdout, NULL);
	if (argc == 2) {
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1) {
			perror("Error open file");
			exit(-2);
		}
	} else if (argc > 2) {
		file_descriptor = -1;
	} else {
		file_descriptor = STDIN_FILENO;
	}

	// 1. Test error
	line = get_next_line(100);
	if (line != NULL) {
		printf("Wrong file descriptor but line is't NULL\n");
		exit(1);
	}

	while (1) {
		printf(">");
		line = NULL;
		line = get_next_line(file_descriptor);
		if (line == NULL) {
			printf("%s\n", line);
			return 0;
		}
		printf("%lu: %s", strlen(line), line);
		free(line);
	}
    return 0;
}
