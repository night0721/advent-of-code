#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main() {
    int LINE_LENGTH = 140;
    FILE *inputfile = fopen("./input", "r");
    char line[2048] = { 0 };
    size_t len = 0;
    ssize_t read;
    if (inputfile == NULL) {
        printf("Input file not found. Exiting.");
        exit(1);
    }
    char **lines = malloc(sizeof(char *) * LINE_LENGTH);
    int line_count = 0;
    while (fgets(line, 1024, inputfile)) {
        lines[line_count] = malloc(sizeof(char) * 2048);
        strcpy(lines[line_count], line);
        line_count++;
    }
    int *goodnumbers = malloc(sizeof(int) * 4096);
    int goodnumber_count = 0;
    for (int i = 0; i < LINE_LENGTH; i++) {
        char *line = lines[i];
        for (int j = 0; j < strlen(lines[i]); j++) {
            bool append = false;
            char *number = malloc(sizeof(char) * 2048);
            while (isdigit(*(line + j)) != 0) {
                number[strlen(number)] = line[j];
                // check left and right is symbol or not
                int prev = j - 1;
                int next = j + 1;
                if (prev > 0) {
                    if (line[prev] != '.' && isdigit(line[prev]) == 0) {
                        // append to good numbers
                        append = true;
                    }
                    // check if on first line, as we can't go back further then check is previous line previous char is symbol or not
                    if (i != 0 && lines[i - 1][prev] != '.' && isdigit(lines[i - 1][prev]) == 0) {
                        append = true;
                    }
                    // check if next line exists
                    if (i != LINE_LENGTH - 1 && lines[i + 1][prev] != '.' && isdigit(lines[i + 1][prev]) == 0) {
                        append = true;
                    }
                }
                if (next <= strlen(line) - 1) {
                    if (line[next] != '.' && line[next] != '\n' && isdigit(line[next]) == 0) {
                        append = true;
                    }

                    if (i != 0 && lines[i - 1][next] != '.' && lines[i - 1][next] != '\n' && isdigit(lines[i - 1][next]) == 0) {
                        append = true;
                    }
                    if (i != LINE_LENGTH - 1 && lines[i + 1][next] != '.' && lines[i + 1][next] != '\n' && isdigit(lines[i + 1][next]) == 0) {
                        append = true;
                    }
                }
                if (i != 0 && lines[i - 1][j] != '.' && isdigit(lines[i - 1][j]) == 0) {
                    append = true;
                }
                if (i != LINE_LENGTH - 1 && lines[i + 1][j] != '.' && isdigit(lines[i + 1][j]) == 0) {
                    append = true;
                }
                j++;
            }
            if (append) {
                goodnumbers[goodnumber_count] = atoi(number);
                goodnumber_count++;
                append = false;
            }
            
        }
    }
    int sum = 0;
    for (int i = 0; i < goodnumber_count; i++) {
        sum += goodnumbers[i];
    }
    printf("Sum: %d\n", sum);
}
