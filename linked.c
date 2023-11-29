#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
} *newNode, *first, *last, *temp;

struct node memblock[25];

void linked() {
    int start, size,flag=0;
    printf("Enter start block: ");
    scanf("%d", &start);
    printf("Enter size: ");
    scanf("%d", &size);

    for (int i = start; i < start + size; i++) {
        if (memblock[i].data == 1) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        for (int i = start; i < start + size; i++) {
            memblock[i].data = 1;

            newNode = (struct node *)malloc(sizeof(struct node));
            newNode->data = 1;
            newNode->link = NULL;

            if (first == NULL) {
                first = newNode;
                last = newNode;
            } else {
                last->link = newNode;
                last = newNode;
            }
        }
        printf("File allocated to blocks %d-%d\n", start, start + size - 1);
    } else {
        printf("Some blocks are already allocated.\n");
    }
}

int main() {
    int choice;
    do {
        printf("\n1. Linked\n2. Exit\n");
        printf("Enter the choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                linked();
                break;
            case 2:
                exit(0);
            default:
                printf("Try another option.\n");
        }
    } while (choice != 2);

    return 0;
}