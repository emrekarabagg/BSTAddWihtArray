#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAXCHAR 100000
const int size = 100;
int tree[size];
FILE *fp1;

void parent(int x) {
    while (x != 0) {
        x = (x - 1) / 2;
    }
}

void inOrder(int currentIndex) {
    if (tree[currentIndex] != '\0') {
        inOrder(2 * currentIndex + 1);
        parent(currentIndex);
        fprintf(fp1, "%d-", tree[currentIndex]);
        inOrder(2 * currentIndex + 2);
    }
}
//insert
void addElementTree(int x) {
    int currentIndex = 0;
    while (true) {
        if (tree[currentIndex] == '\0') {
            tree[currentIndex] = x;
            break;
        } else if (tree[currentIndex] <= x) {
            if (tree[currentIndex] == x) {
                break;
            } else
                currentIndex = (2 * currentIndex + 2);
        } else if (tree[currentIndex] >= x) {
            if (tree[currentIndex] == x) {
                break;
            } else
                currentIndex = (2 * currentIndex + 1);
        }
    }
}



int main() {
    clock_t start = clock();
    FILE *fp;
    char str[MAXCHAR];


    char *filename = "/Users/emrekarabag/CLionProjects/311_HW1/input.txt";

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s\n", str);
    fclose(fp);
    char *token = strtok(str, " ");

    int i = 0;
    int numbers[size];
    while (token != NULL) {
        numbers[i] = atoi(token);
        if (token != '\n') {
            token = strtok(NULL, " ");
            printf("%d ", token);
        }

        i++;
    }
    //build
    for (int i = 0; i < size; i++) {
        addElementTree(numbers[i]);
    }


    fp1 = fopen("/Users/emrekarabag/CLionProjects/311_HW1/test2.txt", "w");
    inOrder(0);
    fclose(fp1);

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\n--- %f seconds ---", elapsed);

    return 0;
}