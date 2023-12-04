#include "../../util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    int id;
    int colors[3];
} game;

int main() {
    FILE *inputfile = fopen("./input", "r");
    char line[1024] = { 0 };
    int sum = 0;
    size_t len = 0;
    ssize_t read;
    if (inputfile == NULL) {
        printf("Input file not found. Exiting.");
        exit(1);
    }
    while (fgets(line, 1024, inputfile)) {
        int colors[3] = { 0, 0, 0 };
        line[strcspn(line, "\n")] = 0;
        char **splitted = str_split(line, ':');
        char *id = str_split(splitted[0], ' ')[1];
        char **sets = str_split(splitted[1], ';');
        bool ok = true;
        for (int i = 0; sets[i]; i++) {
            int colors[3] = { 0, 0, 0 };
            sets[i] = trimwhitespace(sets[i]);
            char **subset = str_split(sets[i], ',');
            for (int j = 0; subset[j]; j++) {
                subset[j] = trimwhitespace(subset[j]);
                char **splittedsubset = str_split(subset[j], ' ');
                char *count = splittedsubset[0];
                char *color = splittedsubset[1];
                if (strncmp(color, "red", 3) == 0) {
                    colors[0] = atoi(count);
                } else if (strncmp(color, "green", 5) == 0) {
                    colors[1] = atoi(count);
                } else if (strncmp(color, "blue", 4) == 0) {
                    colors[2] = atoi(count);
                }
            }
            if (colors[0] > 12 || colors[1] > 13 || colors[2]> 14) {
                    ok = false;
            }
        }
        if (ok) {
            sum += atoi(id);
        }
        free(splitted);
    }
    fclose(inputfile);
    printf("%d\n", sum);
    return 0;
}
