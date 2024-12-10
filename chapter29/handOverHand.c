#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Node {
    int data;
    pthread_mutex_t lock;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

int list_init(List *list) {
    list->head = NULL;
    return 0;
}

int list_insert(List *list, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }
    new_node->data = data;
    if (pthread_mutex_init(&new_node->lock, NULL) != 0) {
        free(new_node);
        return -1;
    }

    pthread_mutex_lock(&new_node->lock);
    if (list->head == NULL) {
        list->head = new_node;
        new_node->next = NULL;
        pthread_mutex_unlock(&new_node->lock);
        return 0;
    }

    pthread_mutex_lock(&list->head->lock);
    new_node->next = list->head;
    list->head = new_node;
    pthread_mutex_unlock(&new_node->lock); // Unlock new node after linking
    pthread_mutex_unlock(&list->head->next->lock); // Unlock previous head
    return 0;
}

int list_contains(List *list, int data) {
    if(list->head == NULL)
       return 0;
   
    pthread_mutex_lock(&list->head->lock);
    Node* current = list->head;

    while (current != NULL) {
        if (current->data == data) {
            pthread_mutex_unlock(&current->lock);
            return 1;
        }
        
        Node* temp = current;
        current = temp->next;

        if(current != NULL)
             pthread_mutex_lock(&current->lock);

        pthread_mutex_unlock(&temp->lock);
    }

    return 0;
}

void list_free(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        pthread_mutex_destroy(&current->lock);
        free(current);
        current = next;
    }
}

void *f1(void *arg) {
    List *li = (List *) arg;
    for (int i = 5; i < 10; i++) {
        printf("Thread 1 inserting element\n");
        list_insert(li, i);
    }
}

void *f2(void *arg) {
    List *li = (List *) arg;
    for (int i = 10; i < 15; i++) {
        printf("Thread 2 inserting element\n");
        list_insert(li, i);
    }
}

int main() {
    List my_list;
    list_init(&my_list);

    pthread_t p1;
    pthread_t p2;

    if (pthread_create(&p1, NULL, f1, &my_list) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    if (pthread_create(&p2, NULL, f2, &my_list) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        printf("Main inserting element\n");
        list_insert(&my_list, i);
    }

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    
    for (int i = 0; i < 15; i++) {
        printf("Contains %d: %s\n", i, list_contains(&my_list, i) ? "Yes" : "No");
    }

    list_free(&my_list);

    return 0;
}