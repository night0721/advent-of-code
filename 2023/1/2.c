#include "../../util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char* value;
} number;

int main() {
    FILE *inputfile = fopen("./input", "r");
    char *line = malloc(sizeof(char) * 100);
    number numbers[9];
    char *names[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    char *values[9] = { "on1e", "tw2o", "th3ree", "fo4ur", "fi5ve", "si6x", "se7ven", "ei8ght", "ni9ne" }; 
    for (int k = 0; k < 9; k++) {
        numbers[k].name = names[k];
        numbers[k].value = values[k];
    }
    int sum = 0;
    size_t len = 0;
    ssize_t read;
    if (inputfile == NULL) {
        printf("Input file not found. Exiting.");
        exit(1);
    }
    while (fgets(line, 100, inputfile)) {
        int length = strlen(line);
        char *cpline = malloc(sizeof(char) * 1024);
        strcpy(cpline, line);
        for (int i = 0; i < 9; i++) {
            char *name = numbers[i].name;
            
            char *value = numbers[i].value;
            replace(cpline, name, value);
        }
        char *concat = malloc(sizeof(char) * strlen(cpline));
        for (int j = 0; j < strlen(cpline) - 1; j++) {
            int currentChar = (int) cpline[j];
            if (currentChar >= '0' && currentChar <= '9') {
                concat[strlen(concat)] = cpline[j];
            }
        }
        char trimmed[3] = { 0 };
        trimmed[0] = concat[0];
        trimmed[1] = concat[strlen(concat) - 1];
        sum += atoi(trimmed);
    }
    fclose(inputfile);
    printf("%d\n", sum); 
}
