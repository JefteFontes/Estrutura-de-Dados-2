#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25

int numbers[MAX_N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
int binarytree[MAX_N * 2];

void constructBalancedTree(int start, int end, int next_index) {
    if (start > end)
        return;

    int mid = (start + end) / 2;

    binarytree[next_index] = numbers[mid];

    constructBalancedTree(start, mid - 1, (next_index * 2) + 1);
    constructBalancedTree(mid + 1, end, (next_index * 2) + 2);
}

int main(){
    int size = sizeof(numbers) / sizeof(numbers[0]);

    constructBalancedTree(0, size - 1, 0);

    for(int i = 0; i < MAX_N * 2; i++) {
        if(binarytree[i] == 0){  
            printf("%d:-\n", i);
        } else {printf("%d: %d\n", i, binarytree[i]);}
    }
    return 0;
}