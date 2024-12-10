#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct Node {
    int dest;
    struct Node* next;
};

struct AdjList {
    struct Node* head;
};

struct Graph {
    int V;
    struct AdjList* array;
    pthread_mutex_t lock;
};

struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;

    pthread_mutex_init(&graph->lock, NULL);
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    pthread_mutex_lock(&graph->lock);
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    pthread_mutex_unlock(&graph->lock);
}

void printGraph(struct Graph* graph) {
    pthread_mutex_lock(&graph->lock);
    for (int v = 0; v < graph->V; v++) {
        struct Node* crawl = graph->array[v].head;
        printf("\nVertex %d\n head ", v);
        while (crawl) {
            printf("-> %d", crawl->dest);
            crawl = crawl->next;
        }
        printf("\n");
    }
    pthread_mutex_unlock(&graph->lock);
}

struct ThreadData {
    struct Graph* graph;
    int numEdgesToAdd;
};

void* addEdgesConcurrently(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    struct Graph* graph = data->graph;
    int numEdgesToAdd = data->numEdgesToAdd;
    
    srand(time(NULL) + pthread_self()); 

    for (int i = 0; i < numEdgesToAdd; i++) {
        int src = rand() % graph->V;
        int dest = rand() % graph->V;
        
        while (src == dest) {
           dest = rand() % graph->V; 
        }

        addEdge(graph, src, dest);
        
    }

    pthread_exit(NULL);
}

int main() {
    int V = 10;
    int numThreads = 4;
    int numEdgesPerThread = 5;

    struct Graph* graph = createGraph(V);
    pthread_t threads[numThreads];
    struct ThreadData threadData[numThreads];

   
    for (int i = 0; i < numThreads; i++) {
        threadData[i].graph = graph;
        threadData[i].numEdgesToAdd = numEdgesPerThread;
        if (pthread_create(&threads[i], NULL, addEdgesConcurrently, &threadData[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    printGraph(graph);

    pthread_mutex_destroy(&graph->lock);
    for (int i = 0; i < V; i++) {
      struct Node* current = graph->array[i].head;
      while (current != NULL){
        struct Node* next = current->next;
        free(current);
        current = next;
      }
    }

    free(graph->array);
    free(graph);

    return 0;
}