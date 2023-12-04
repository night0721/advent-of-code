#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);
    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;
    result = malloc(sizeof(char*) * count);
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}

// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

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
