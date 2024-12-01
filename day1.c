#include <stdio.h>
#include <stdlib.h>

int similatiryf(int left[], int leftSize, int right[], int rightSize) {
    int score = 0;

    for (int i = 0; i < leftSize; i++) {
        int count = 0;
        for (int j = 0; j < rightSize; j++) {
            if (left[i] == right[j]) {
                count++;
            }
        }
        score += left[i] * count;
    }

    return score;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int distancef(int left[], int leftSize, int right[], int rightSize) {
    if (leftSize != rightSize) {
        printf("Error: Lists must have the same number of elements.\n");
        return -1;
    }

    qsort(left, leftSize, sizeof(int), compare);
    qsort(right, rightSize, sizeof(int), compare);
    int totalDistance = 0;

    for (int i = 0; i < leftSize; i++) {
        totalDistance += abs(left[i] - right[i]);
    }

    return totalDistance;
}


int main() {
    FILE *file = fopen("day1_input.txt", "r");
    if (file == NULL) {
        printf("brak danych");
        return 1;
    }

   int *left = NULL;
   int *right = NULL;
   int leftSize = 0, rightSize = 0;

   int capacity = 10;
   left = malloc(capacity * sizeof(int));
   right = malloc(capacity * sizeof(int));

   if (left == NULL || right == NULL) {
      printf("cos sie zjebalo z lokacja");
      fclose(file);
      return 1;
   }

   int tempLeft, tempRight;
   while (fscanf(file, "%d %d", &tempLeft, &tempRight) == 2) {
      if (leftSize == capacity) {
         capacity *= 2;
         left = realloc(left, capacity * sizeof(int));
         right = realloc(right, capacity * sizeof(int));
            if (left == NULL || right == NULL) {
               printf("cos sie zjebalo z relokacja");
               fclose(file);
               free(left);
               free(right);
               return 1;
            }
     }

     left[leftSize++] = tempLeft;
     right[rightSize++] = tempRight;
   }

   fclose(file);
   int similarity = similatiryf(left, leftSize, right, rightSize);
   int distance = distancef(left, leftSize, right, rightSize);
   printf("p1: %d\n", similarity);
   printf("p2: %d\n", distance);
   free(left);
   free(right);

   return 0;
}