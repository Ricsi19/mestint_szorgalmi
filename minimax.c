#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* middle;
    struct Node* right;
} Node;

// Csomópont létrehozása
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->middle = NULL;
    newNode->right = NULL;
    return newNode;
}

// Bemenet olvasása
int* readInput(int* n) {
    char input[500];
    printf("Kerem adja meg a fat listakent abrazolva: ");
    fgets(input, sizeof(input), stdin);
    int* treeArray = NULL;
    *n = 0;
    int capacity = 10;
    treeArray = (int*)malloc(capacity * sizeof(int));
    char* token = strtok(input, " \n");
    while (token != NULL) {
        if (*n >= capacity) {
            capacity *= 2;
            int* temp = (int*)realloc(treeArray, capacity * sizeof(int));
            if (temp == NULL) {
                free(treeArray);
                *n = 0;
                return NULL;
            }
            treeArray = temp;
        }
        if (strcmp(token, "x") == 0) {
            treeArray[*n] = -1; // Nem ismert
        } else if (strcmp(token, ".") == 0) {
            treeArray[*n] = 0; // Üres levél
        } else {
            treeArray[*n] = (int)strtol(token, NULL, 10); // Convert to integer
        }
        (*n)++;
        token = strtok(NULL, " \n");
    }
    return treeArray;
}

// Fa építése
Node* buildTree(int* treeArray, int index, int n) {
    if (index >= n) {
        return NULL; // Ha az index túllép a tömbön
    }

    Node* node = createNode(treeArray[index]);

    // Gyerekek hozzáadása
    int leftIndex = 3 * index + 1;
    int middleIndex = 3 * index + 2;
    int rightIndex = 3 * index + 3;

    if (leftIndex < n) node->left = buildTree(treeArray, leftIndex, n);
    if (middleIndex < n) node->middle = buildTree(treeArray, middleIndex, n);
    if (rightIndex < n) node->right = buildTree(treeArray, rightIndex, n);

    return node;
}

// Max függvény
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Min függvény
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Minimax algoritmus
int minmax(Node* node, int isMaximizing) {
    if (node == NULL) {
        return 0; // Empty node, return neutral value
    }

    // Ha levél csúcs vagy 'x' (ismeretlen érték)
    if (node->value != -1) {
        return node->value;
    }

    if (isMaximizing) {
        int bestValue = INT_MIN;
        if (node->left) bestValue = max(bestValue, minmax(node->left, 0));
        if (node->middle) bestValue = max(bestValue, minmax(node->middle, 0));
        if (node->right) bestValue = max(bestValue, minmax(node->right, 0));
        node->value = bestValue; // Store the calculated value
        return bestValue;
    } else {
        int bestValue = INT_MAX;
        if (node->left) bestValue = min(bestValue, minmax(node->left, 1));
        if (node->middle) bestValue = min(bestValue, minmax(node->middle, 1));
        if (node->right) bestValue = min(bestValue, minmax(node->right, 1));
        node->value = bestValue; // Store the calculated value
        return bestValue;
    }
}

void freeTree(Node* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->middle);
    freeTree(node->right);
    free(node);
}

int main() {
    int n;
    int* treeArray = readInput(&n);

    clock_t start = clock();

    Node* root = buildTree(treeArray, 0, n);
    if (root != NULL) {
        printf("A fa sikeresen felepult.\n");
        int maxProfit = minmax(root, 1);
        printf("A maximalisan elerheto nyereseg: %d\n", maxProfit);
    } else {
        printf("A fa nem epult fel megfeleloen.\n");
    }

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Az algoritmus futasi ideje: %f masodperc\n", cpu_time_used);

    freeTree(root);
    free(treeArray);
    return 0;
}