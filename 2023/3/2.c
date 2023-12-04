#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    int line;
    int index;
    int values[9];
} star;

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
    int range[3] = { -1, 0, 1 };
    star *gears = malloc(sizeof(star) * 4096);
    int gear_count = 0;
    
    int answer = 0;
    for (int i = 0; i < LINE_LENGTH; i++) {
        int n = 0;
        char *line = lines[i];
        line[strlen(line) - 1] = '\0';
        bool havegear = false;
        star gear = (star) { 0, 0 };
        for (int j = 0; j < strlen(line); j++) {
            if (isdigit(line[j]) != 0) {
                n = n * 10 + line[j] - '0';
                for (int ii = 0; ii < 3; ii++) {
                    for (int jj = 0; jj < 3; jj++) {
                        if (i + range[ii] >= 0 && i + range[ii] < LINE_LENGTH && j + range[jj] >= 0 && j + range[jj] < strlen(lines[i])) {
                            char cc = lines[i + range[ii]][j + range[jj]];
                            if (cc != '.' && isdigit(cc) == 0 && cc == '*') {
                                gear = (star) { i + range[ii], j + range[jj], {} };
                                havegear = true;
                            }
                        }
                    }
                }
            }
            if (j == strlen(lines[i]) - 1 || isdigit(line[j]) == 0) {
                if (havegear) {
                    int gearcounter = 0;
                    int found_i = -1;
                    for (int k = 0; k < gear_count; k++) {
                        if (gears[k].line == gear.line && gears[k].index == gear.index) {
                            found_i = k;
                            break;
                        }
                    }
                    if (found_i == -1) {
                        gears[gear_count] = gear;
                        gears[gear_count].values[0] = n;
                        gear_count++;
                    } else {
                        int length = 0;
                        for (int k = 0; k < 9; k++) {
                            if (gears[found_i].values[k] != 0) {
                                length++;
                            }
                        }
                        gears[found_i].values[length] = n;
                        length += 1;
                        if (length == 2) {
                            answer += gears[found_i].values[0] * n;
                        }
                    }
                    havegear = false;
                }
                n = 0;
            }
        }
    }
    printf("Sum: %d\n", answer);
}
