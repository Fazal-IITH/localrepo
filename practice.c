// Insert Heap
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int capacity;
    int *arr;
} Heap;

Heap* createHeap(int capacity) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->size = 0;
    h->capacity = capacity;
    h->arr = (int*)malloc((capacity + 1) * sizeof(int)); // index starts at 1
    return h;
}

void insert(Heap* h, int x) {
    h->size++;
    int i = h->size;
    h->arr[i] = x;

    while (i > 1 && h->arr[i] < h->arr[i/2]) { // min-heap
        int temp = h->arr[i];
        h->arr[i] = h->arr[i/2];
        h->arr[i/2] = temp;
        i /= 2;
    }
}

int main() {
    Heap* h = createHeap(10);

    insert(h, 40);
    insert(h, 20);
    insert(h, 10);
    insert(h, 30);

    printf("Heap array:\n");
    for (int i = 1; i <= h->size; i++)
        printf("%d ", h->arr[i]);
}


// Max-Heapify

void maxHeapify(int A[], int heapSize, int i) {
    int l = 2 * i;         // LEFT(i)
    int r = 2 * i + 1;     // RIGHT(i)
    int largest = i;

    // Compare with left child
    if (l <= heapSize && A[l] > A[i]) {
        largest = l;
    } else {
        largest = i;
    }

    // Compare with right child
    if (r <= heapSize && A[r] > A[largest]) {
        largest = r;
    }

    // If largest is not the root i, swap and continue heapifying
    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        maxHeapify(A, heapSize, largest);
    }
}
//Extract-Max
int extractMax(Heap* h) {
    if (h->size < 1) {
        printf("Heap underflow!\n");
        return -1;
    }

    int max = h->arr[1];                 // line 3 of pseudocode
    h->arr[1] = h->arr[h->size];         // line 4
    h->size = h->size - 1;               // line 5
    maxHeapify(h->arr,h->size, 1);                    // line 6
    return max;                          // line 7
}

//Increase Key
#include <stdio.h>

void heapIncreaseKey(Heap* h, int i, int key) {
    if (key < h->arr[i]) {
        printf("Error: new key is smaller than current key\n");
        return;
    }

    h->arr[i] = key;   // line 3

    // Bubble up (same logic as insert)
    while (i > 1 && h->arr[i/2] < h->arr[i]) {   // line 4
        int temp = h->arr[i];
        h->arr[i] = h->arr[i/2];
        h->arr[i/2] = temp;

        i = i / 2;   // line 6
    }
}

//Build Heap
void buildMaxHeap(Heap* h) {
    h->size = h->capacity;   // A.heap-size = A.length

    for (int i = h->size / 2; i >= 1; i--) {   // i = ⌊n/2⌋ downto 1
        maxHeapify(h, i);                     // Max-Heapify(A, i)
    }
}

//Heap Sort
void heapSort(int A[],int n) {
    buildMaxHeap(A);

    for (int i = n - 1; i >= 1; i--) {
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;

        maxHeapify(A, i, 0);  
    }
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dest;
    struct Node *next;
} Node;

typedef struct {
    int V;        // number of vertices
    Node **adj;   // adjacency lists
} Graph;

// create a new adjacency list node
Node* new_node(int v) {
    Node* n = malloc(sizeof(Node));
    n->dest = v;
    n->next = NULL;
    return n;
}

// create a graph with V vertices
Graph* create_graph(int V) {
    Graph* g = malloc(sizeof(Graph));
    g->V = V;
    g->adj = malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

// add edge u–v (undirected)
void add_edge(Graph* g, int u, int v) {
    Node* n = new_node(v);
    n->next = g->adj[u];
    g->adj[u] = n;

    n = new_node(u);
    n->next = g->adj[v];
    g->adj[v] = n;
}

// -------------------------------------------------------
// BFS exactly like the pseudocode
// -------------------------------------------------------
void BFS(Graph* g, int s) {
    int *level = malloc(g->V * sizeof(int));
    int *parent = malloc(g->V * sizeof(int));

    // mark all vertices as unseen using -1
    for (int i = 0; i < g->V; i++) {
        level[i] = -1;
        parent[i] = -1;
    }

    level[s] = 0;     // level = { s : 0 }
    parent[s] = -1;   // parent = { s : None }

    int i = 1;

    // frontier = [s]
    int frontier_size = 1;
    int *frontier = malloc(sizeof(int));
    frontier[0] = s;

    while (frontier_size > 0) {

        // next = []
        int *next = NULL;
        int next_size = 0;

        // for u in frontier:
        for (int f = 0; f < frontier_size; f++) {
            int u = frontier[f];

            // for v in Adj[u]:
            for (Node* p = g->adj[u]; p != NULL; p = p->next) {
                int v = p->dest;

                // if v not in level (i.e., unseen):
                if (level[v] == -1) {
                    level[v] = i;
                    parent[v] = u;

                    // next.append(v)
                    next_size++;
                    next = realloc(next, next_size * sizeof(int));
                    next[next_size - 1] = v;
                }
            }
        }

        free(frontier);
        frontier = next;
        frontier_size = next_size;

        i += 1;
    }

    // print results
    printf("Vertex | Level | Parent\n");
    for (int v = 0; v < g->V; v++)
        printf("%6d | %5d | %6d\n", v, level[v], parent[v]);

    free(frontier);
    free(level);
    free(parent);
}

// ---------------------------
// Example usage
// ---------------------------
int main() {
    Graph* g = create_graph(6);

    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 1, 3);
    add_edge(g, 2, 4);
    add_edge(g, 3, 5);

    BFS(g, 0);
}


#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
    int data;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode *front, *rear;
} Queue;

// Create a new queue node
QNode* createQNode(int value) {
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->data = value;
    node->next = NULL;
    return node;
}

// Create an empty queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return (q->front == NULL);
}

// Enqueue operation
void enqueue(Queue* q, int value) {
    QNode* node = createQNode(value);

    if (q->rear == NULL) {  // empty queue
        q->front = q->rear = node;
        return;
    }

    q->rear->next = node;
    q->rear = node;
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow!\n");
        return -1;
    }

    QNode* temp = q->front;
    int value = temp->data;

    q->front = q->front->next;

    if (q->front == NULL)  // queue became empty
        q->rear = NULL;

    free(temp);
    return value;
}
#define WHITE 0
#define GRAY 1
#define BLACK 2
// ---------- BFS (exact CLRS pseudocode) ----------
void BFS(Graph* g, int s) {
    int V = g->V;

    int* color = (int*)malloc(V * sizeof(int));
    int* d = (int*)malloc(V * sizeof(int));
    int* pi = (int*)malloc(V * sizeof(int));

    // Step 1–4: Initialization
    for (int u = 0; u < V; u++) {
        if (u != s) {
            color[u] = WHITE;
            d[u] = 1e9;      // infinity
            pi[u] = -1;      // NIL
        }
    }

    // Step 5–7: Initialize source
    color[s] = GRAY;
    d[s] = 0;
    pi[s] = -1;

    Queue* Q = createQueue();   // Step 8
    enqueue(Q, s);              // Step 9

    // Step 10
    while (!isEmpty(Q)) {
        int u = dequeue(Q);     // Step 11

        // Step 12: explore neighbors
        Node* temp = g->adj[u];
        while (temp != NULL) {
            int v = temp->dest;

            if (color[v] == WHITE) {   // Step 13
                color[v] = GRAY;       // Step 14
                d[v] = d[u] + 1;       // Step 15
                pi[v] = u;             // Step 16
                enqueue(Q, v);         // Step 17
            }

            temp = temp->next;
        }

        color[u] = BLACK;              // Step 18
    }

    // Print results
    printf("Vertex\tColor\tDist\tParent\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\t%d\t%d\n", i, color[i], d[i], pi[i]);
}

void DFS_visit(Graph* g, int s, int parent[]) {
    Node* temp = g->adj[s];

    while (temp != NULL) {
        int v = temp->dest;

        if (parent[v] == NULL) {
            parent[v] = s;
            DFS_visit(g, v, parent);    // recursive call
        }
        temp = temp->next;
    }
}

// ---------- DFS(G) ----------
void DFS(Graph* g) {
    int parent[g->V];

    // initialize parent array to NIL
    for (int i = 0; i < g->V; i++)
        parent[i] = NULL;

    // for every vertex
    for (int v = 0; v < g->V; v++) {
        if (parent[v] == NULL) {
            parent[v] = v;      // root of a DFS tree
            DFS_visit(g, v, parent);
        }
    }
}

int timer = 0;

// DFS arrays
int start[100], finish[100], visited[100], parent[100];

void DFS(Node* adj[], int u) {
    visited[u] = 1;
    start[u] = ++timer;

    Node* temp = adj[u];
    while (temp != NULL) {
        int v = temp->dest;

        if (start[v] == 0) {
            // Tree edge
            parent[v] = u;
            printf("Tree Edge: %d -> %d\n", u, v);
            DFS(adj, v);

        } else if (finish[v] == 0) {
            // Back edge (to ancestor)
            printf("Back Edge: %d -> %d\n", u, v);

        } else if (start[u] < start[v] && finish[v] < finish[u]) {
            // Forward edge
            printf("Forward Edge: %d -> %d\n", u, v);

        } else if(finish[v] < start[u]){
            // Cross edge
            printf("Cross Edge: %d -> %d\n", u, v);
        }

        temp = temp->next;
    }

    finish[u] = ++timer;
}


//topo sort
int visited[100];
Node* topoHead = NULL;   // head of the linked list

// Insert vertex at the front of the linked list
void insertFront(int v) {
    Node* n = createNode(v);
    n->next = topoHead;
    topoHead = n;
}

void DFS_Topo(Node* adj[], int u) {
    visited[u] = 1;

    for (Node* temp = adj[u]; temp != NULL; temp = temp->next) {
        int v = temp->dest;
        if (!visited[v])
            DFS_Topo(adj, v);
    }

    // Insert vertex at front when finished
    insertFront(u);
}

// Topological sort for directed acyclic graph
void topologicalSort(Node* adj[], int n) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++)
        if (!visited[i])
            DFS_Topo(adj, i);
}


//kahn topo
void kahnToposort(Node* adj[], int n) {
    int indegree[100] = {0};

    // Step 1: Compute indegree of all vertices
    for (int u = 0; u < n; u++) {
        for (Node* temp = adj[u]; temp != NULL; temp = temp->next) {
            indegree[temp->vertex]++;
        }
    }

    Queue q;
    initQueue(&q);

    // Step 2: Enqueue all vertices with indegree 0
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0)
            enqueue(&q, i);
    }

    int topo[100];
    int idx = 0;

    // Step 3: BFS processing
    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        topo[idx++] = u;

        // Reduce indegree of all neighbors
        for (Node* temp = adj[u]; temp != NULL; temp = temp->next) {
            int v = temp->vertex;
            indegree[v]--;

            if (indegree[v] == 0)
                enqueue(&q, v);
        }
    }

    // Step 4: Check if cycle exists
    if (idx != n) {
        printf("Graph contains a cycle. Topological sort not possible.\n");
        return;
    }

    printf("Topological Order (Kahn's Algorithm):\n");
    for (int i = 0; i < idx; i++)
        printf("%d ", topo[i]);
    printf("\n");
}

// Kruskal algo
#include <stdio.h>

#define INF 999999

// ---------- Disjoint Set (Union-Find) ----------
int parent[100];

void makeSet(int v) {
    parent[v] = v;
}

int findSet(int v) {
    if (parent[v] == v)
        return v;
    return parent[v] = findSet(parent[v]);   // path compression
}

void unionSet(int u, int v) {
    u = findSet(u);
    v = findSet(v);
    parent[v] = u;      // simple union
}

// ---------- Edge Structure ----------
typedef struct {
    int u, v, w;
} Edge;

// ----------------------------------------------------------
int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int graph[100][100];
    printf("Enter adjacency matrix (0 for no edge):\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    // ---------- Step 1: A = ∅ (MST edges stored) ----------
    Edge MST[100];
    int mstCount = 0;

    // ---------- Step 2: MAKE-SET(v) for each vertex ----------
    for (int i = 0; i < n; i++)
        makeSet(i);

    // ---------- Step 3: Create list of edges ----------
    Edge edges[10000];
    int edgeCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != 0) {
                edges[edgeCount].u = i;
                edges[edgeCount].v = j;
                edges[edgeCount].w = graph[i][j];
                edgeCount++;
            }
        }
    }

    // ---------- Step 4: Sort edges by weight ----------
    for (int i = 0; i < edgeCount; i++) {
        for (int j = 0; j < edgeCount - 1 - i; j++) {
            if (edges[j].w > edges[j + 1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // ---------- Step 5: For each edge in sorted list ----------
    int mstWeight = 0;

    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        // Step 6: If FIND-SET(u) != FIND-SET(v)
        if (findSet(u) != findSet(v)) {

            // Step 7: A = A ∪ {(u, v)}
            MST[mstCount++] = edges[i];
            mstWeight += edges[i].w;

            // Step 8: UNION(u, v)
            unionSet(u, v);
        }
    }

    // ---------- Step 9: Print MST ----------
    printf("\nMST using Kruskal:\n");
    for (int i = 0; i < mstCount; i++) {
        printf("%d -- %d  weight = %d\n",
               MST[i].u, MST[i].v, MST[i].w);
    }

    printf("\nTotal MST Weight = %d\n", mstWeight);

    return 0;
}



 
 



