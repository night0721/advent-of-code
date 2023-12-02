#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

typedef struct {
    int id;
    int colors[3];
} game;

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
        int maxes[3] = { 0, 0, 0 };
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
                if (colors[0] > maxes[0]) {
                    maxes[0] = colors[0];
                }
                if (colors[1] > maxes[1]) {
                    maxes[1] = colors[1];
                }
                if (colors[2] > maxes[2]) {
                    maxes[2] = colors[2];
                }
            }
        }
        sum += maxes[0] * maxes[1] * maxes[2];
        free(splitted);
    }
    fclose(inputfile);
    printf("%d\n", sum);
    return 0;
}
