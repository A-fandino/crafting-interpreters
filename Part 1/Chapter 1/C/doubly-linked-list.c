#include <stdlib.h>
#include <stdio.h>

typedef struct LinkedList {
    char* value;
    struct LinkedList* next;
    struct LinkedList* prev;
} LinkedList;

typedef enum{
    PREV,
    NEXT
} Position;

LinkedList* insert(LinkedList* reference, char* value, Position position) {
    LinkedList* node = (LinkedList *)malloc(sizeof(LinkedList));
    node->value = value;
    if (position == PREV) {
        reference->prev = node;
        node->next = reference;
        return node;
    }
    node->prev = reference;
    reference->next = node;
    return node;
}

LinkedList * find(LinkedList* reference, char* search, Position direction) {
    LinkedList* next;
    int idx = 0;
    for(;search[idx] != '\0' && search[idx] == reference->value[idx]; idx++);
    if (search[idx] == reference->value[idx]) {
        return reference;
    }
    if (direction == PREV) {
        next = reference->prev;
    } else {
        next = reference->next;
    }
    if (!next) return 0;
    return find(next, search, direction);
}

void delete(LinkedList* reference) {
    if (reference->next) reference->next->prev = reference->prev;
    if (reference->prev) reference->prev->next = reference->next;
    reference->next=0;
    reference->prev=0;
    free(reference);
}

int main() {
    LinkedList* node = (LinkedList*)malloc(sizeof(LinkedList));
    node->value = "abc";
    printf("Node %s\n", node->value);
    LinkedList* node2 = insert(node, "Node 2", PREV);
    LinkedList* node3 = insert(node, "Node 3", NEXT);

    printf("Found: %s\n", find(node, "Node 2", PREV)->value);
    printf("Found: %s\n", find(node, "Node 3", NEXT)->value);
    printf("Not Found: %s\n", find(node, "Node 4", NEXT));
    printf("Not Found: %s\n", find(node, "Node 4", PREV));

    delete(node);

    printf("Node 2->next: %s\n", node2->next->value);
    printf("Node 3->prev: %s\n", node3->prev->value);
    printf("Node %s\n", node->value);

}
