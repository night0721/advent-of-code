#include "../../util.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    FILE *inputfile = fopen("./input", "r");
    char line[2048] = { 0 };
    size_t len = 0;
    ssize_t read;
    if (inputfile == NULL) {
        printf("Input file not found. Exiting.");
        exit(1);
    }
    char **lines = malloc(sizeof(char *) * 1024);
    int total = 0;
    while (fgets(line, 2048, inputfile)) {
        char **split = str_split(line, '|');
        char *left = split[0];
        char *right = split[1];
        
        int *win_num = malloc(sizeof(int) * 1024);
        char *winning_numbers = str_split(left, ':')[1];
        winning_numbers = trimwhitespace(winning_numbers);
        // check consecutive space then shift characters to left
        for (int i = 0; i < strlen(winning_numbers); i++) {
            if (winning_numbers[i] == ' ' && winning_numbers[i + 1] == ' ') {
                // shift chracters to left
                for (int j = i; j < strlen(winning_numbers); j++) {
                    winning_numbers[j] = winning_numbers[j + 1];
                }
            }
        }
        char **winning_numbers_split = str_split(winning_numbers, ' ');
        int winning_count = 0;
        while (winning_numbers_split[winning_count] != NULL) {
            win_num[winning_count] = atoi(winning_numbers_split[winning_count]);
            winning_count++;
        }
        int *gambled_num = malloc(sizeof(int) * 1024);
        right = trimwhitespace(right);
        // check consecutive space then shift characters to left
        for (int i = 0; i < strlen(right); i++) {
            if (right[i] == ' ' && right[i + 1] == ' ') {
                // shift chracters to left
                for (int j = i; j < strlen(right); j++) {
                    right[j] = right[j + 1];
                }
            }
        }

        char **gambled_numbers = str_split(right, ' ');
        int gambled_count = 0;
        int score = 0;
        while (gambled_numbers[gambled_count] != NULL) {
            int winning_counter = 0;
            gambled_num[gambled_count] = atoi(gambled_numbers[gambled_count]);
            while (win_num[winning_counter] != NULL) {
                if (gambled_num[gambled_count] == win_num[winning_counter]) {
                    if (score != 1 && score > 0) score *= 2;
                    else score++;
                }
                winning_counter++;
            }
            gambled_count++;
        }
       total += score;
    }
    printf("Sum: %d\n", total);
}
