//
//  main.c
//  get_next_line
//
//  Created by Dmitriy Borovikov on 26.06.2021.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char *argv[]) {
	char *line;
	int rezult;
	int file_descriptor;

	setbuf(stdout, NULL);
	if (argc >= 2) {
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1) {
			perror("Error open file");
			exit(-2);
		}
	} else {
		file_descriptor = STDIN_FILENO;
	}
	while (1) {
		printf(">");
		rezult = get_next_line(file_descriptor, &line);
		if (rezult <= 0)
			return rezult;
		printf("%d: '%s'\n", rezult, line);
		free(line);
	}
    return 0;
}
