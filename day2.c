#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_LEVELS 100

bool is_safe(int levels[], int size) {
    if (size < 2) return false; 

    bool increasing = true, decreasing = true;

    for (int i = 0; i < size - 1; i++) {
        int diff = levels[i + 1] - levels[i];

        
        if (diff < -3 || diff > 3 || diff == 0) {
            return false;
        }

       
        if (diff > 0) {
            decreasing = false;
        } else if (diff < 0) {
            increasing = false;
        }
    }

    return increasing || decreasing;
}

bool is_safe_with_dampener(int levels[], int size) {
    if (is_safe(levels, size)) return true;

    for (int i = 0; i < size; i++) {
        int temp_levels[MAX_LEVELS];
        int temp_size = 0;

        for (int j = 0; j < size; j++) {
            if (j != i) { 
                temp_levels[temp_size++] = levels[j];
            }
        }

        if (is_safe(temp_levels, temp_size)) {
            return true;
        }
    }

    return false;
}

int main() {
    FILE *file = fopen("day2_input.txt", "r");
    if (!file) {
        printf("brak danych");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int safe_count = 0;
	int safe_dampener_count = 0;
    
    while (fgets(line, sizeof(line), file)) {
        int levels[MAX_LEVELS];
        int size = 0;

        
        char *token = strtok(line, " \n");
        while (token) {
            levels[size++] = atoi(token);
            token = strtok(NULL, " \n");
        }

       
        if (is_safe(levels, size)) {
            safe_count++;
        }

        if (is_safe_with_dampener(levels, size)) {
            safe_dampener_count++;
        }
    }

    fclose(file);

    printf("p1: %d\n", safe_count);
    printf("p2: %d\n", safe_dampener_count);


    return 0;
}