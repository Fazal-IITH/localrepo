#include <stdio.h>
 #include <stdlib.h>
 
 #define MAXN 1000
 #define MAXDEG MAXN
 
 /* ---------------- Graph Representation ---------------- */
 int adj[MAXN][MAXDEG];
 int deg[MAXN];
 
 /* ---------------- BFS Output Data ---------------- */
 int dist[MAXN];
 int parent[MAXN];
 
 /* ---------------- Queue (Dynamic Circular Buffer), DO not modify ---------------- */
 
 typedef struct {
     int *data;
     int head, tail;
     int cap;
 } Queue;
 
 /* === Queue Implementation (PROVIDED) === */
 void queue_init(Queue *q, int init_cap) {
     if (init_cap < 2) init_cap = 2;
     q->data = malloc(init_cap * sizeof(int));
     if (!q->data) { perror("malloc"); exit(EXIT_FAILURE); }
     q->cap = init_cap;
     q->head = q->tail = 0;
 }
 
 int queue_empty(const Queue *q) {
     return q->head == q->tail;
 }
 
 void queue_push(Queue *q, int x) {
     int next = (q->tail + 1) % q->cap;
     if (next == q->head) {
         /* Resize if full */
         int newcap = q->cap * 2;
         int *newdata = malloc(newcap * sizeof(int));
         if (!newdata) { perror("malloc"); exit(EXIT_FAILURE); }
         int i = 0;
         while (!queue_empty(q)) {
             newdata[i++] = q->data[q->head];
             q->head = (q->head + 1) % q->cap;
         }
         free(q->data);
         q->data = newdata;
         q->cap = newcap;
         q->head = 0;
         q->tail = i;
         next = (q->tail + 1) % q->cap;
     }
     q->data[q->tail] = x;
     q->tail = next;
 }
 
 int queue_pop(Queue *q) {
     if (queue_empty(q)) { fprintf(stderr, "Queue underflow!\n"); exit(EXIT_FAILURE); }
     int v = q->data[q->head];
     q->head = (q->head + 1) % q->cap;
     return v;
 }
 
 void queue_free(Queue *q) {
     free(q->data);
     q->data = NULL;
     q->cap = 0;
     q->head = q->tail = 0;
 }
 
 /* === BFS FUNCTION (TO BE FILLED IN) === */
 void bfs(int n, int s) {
    //int dist[MAXN];
    //int parent[MAXN];
     for(int i=0;i<n;i++){
        dist[i]=-1;
        parent[i]=-1;
     }
     parent[s]=-1;
     dist[s]=0;

     Queue* q=malloc(sizeof(Queue));
     queue_init(q,n);
     queue_push(q,s);
     // int adj[MAXN][MAXDEG];
    // int deg[MAXN];
     while(!queue_empty(q)){
        int u=queue_pop(q);
        for(int i=0;i<deg[u];i++){
            int v=adj[u][i];
            if(dist[v]==-1){
                parent[v]=u;
                dist[v]=dist[u]+1;
                queue_push(q,v);
            }
        }
     }
 }
 
 
 
 /* ---------------- MAIN PROGRAM DO NOT MODIFY ---------------- */
 int main(void) {
     int n, m;
     if (scanf("%d %d", &n, &m) != 2) {
         fprintf(stderr, "Invalid input\n");
         return 1;
     }
 
     for (int i = 0; i < n; i++) deg[i] = 0;
 
     /* Read edges (0-based vertex input) */
     for (int i = 0; i < m; i++) {
         int u, v;
         scanf("%d %d", &u, &v);
         if (u < 0 || u >= n || v < 0 || v >= n) continue;
         adj[u][deg[u]++] = v;
         if (u != v) adj[v][deg[v]++] = u;
     }
 
     int s;
     scanf("%d", &s);
 
     bfs(n, s);
 
     printf("distances:");
     for (int i = 0; i < n; i++) printf(" %d", dist[i]);
     printf("\nparents:");
     for (int i = 0; i < n; i++) printf(" %d", parent[i]);
     printf("\n");
 
     return 0;
 }