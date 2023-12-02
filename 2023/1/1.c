#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *inputfile = fopen("./input", "r");
    char line[100] = { 0 };
    int sum = 0;
    size_t len = 0;
    ssize_t read;
    if (inputfile == NULL) {
        printf("Input file not found. Exiting.");
        exit(1);
    }
    while (fgets(line, 100, inputfile)) {
        int length = strlen(line);
        char *concat = malloc(sizeof(char) * length);
        for (int i = 0; i < length - 1; i++) {
            int currentChar = (int) line[i];
            if (currentChar >= 49 && currentChar <= 57) {
                int len = strlen(concat);
                concat[len] = line[i];
            }
        }
        concat[strlen(concat)] = '\0';
        char trimmed[3] = { 0 };
        trimmed[0] = concat[0];
        trimmed[1] = concat[strlen(concat) - 1];
        trimmed[2] = '\0';
        sum += atoi(trimmed);
    }
    fclose(inputfile);
    printf("Sum: %d\n", sum); 
}
