#include <stdlib.h>
#include <stdio.h>

typedef enum
{
  FALSE, TRUE
} bool;

typedef enum
{
  UNDIRECTED, DIRECTED
} graph_direction_type;

typedef struct adj_node
{
  int vertex;                   // index to adjacency list array
  struct adj_node *next;        // pointer to the next node
} adj_node_t;

typedef struct adj_list
{
  int num_members;              // number of members in the list
  bool visited;                 // is the node represented by this list visited
  adj_node_t *head;             // first node in the linked list
} adj_list_t;

typedef struct graph
{
  graph_direction_type direction;       // type (directed or undirected)
  int num_vertices;             // number of vertices
  adj_list_t *list;             // adjacency list array
} graph_t;


/* Create a new node with the specified value */
adj_node_t *
create_node (int value)
{
  adj_node_t *new_node = (adj_node_t *) malloc (sizeof (adj_node_t));
  new_node->vertex = value;
  new_node->next = NULL;

  return new_node;
}

/* Create a new graph with gtype direction and n vertices */
graph_t *
create_graph (int num, graph_direction_type direction)
{
  int c;

  graph_t *graph = (graph_t *) malloc (sizeof (graph_t));
  graph->direction = direction;
  graph->num_vertices = num;

  /* Create an array of adjacency lists and an array of visited vertices */
  graph->list = (adj_list_t *) malloc (sizeof (adj_list_t));
  //graph->visited = (int *) malloc (sizeof (int));
  for (c = 0; c < num; c++) {
    graph->list[c].head = NULL;
    graph->list[c].visited = FALSE;
  }

  return graph;
}

/* Add an edge from src to dest in the adjacency list */
void
add_edge (graph_t * graph, int src, int dest)
{
  adj_node_t *new_node = create_node (dest);
  new_node->next = graph->list[src].head;       // prepend node to vertex adjacency list
  graph->list[src].head = new_node;
  graph->list[src].num_members++;

  if (graph->direction == UNDIRECTED) {
    /* Add a mirror edge from dest to src */
    new_node = create_node (src);
    new_node->next = graph->list[dest].head;
    graph->list[dest].head = new_node;
    graph->list[dest].num_members++;
  }
}

/* Function to print the adjacency list of graph*/
void
display_graph (graph_t graph)
{
  int c;
  for (c = 0; c < graph.num_vertices; c++) {
    adj_node_t *head = graph.list[c].head;

    printf ("%d: ", c);
    while (head) {
      printf ("%d ", head->vertex);
      head = head->next;
    }

    printf ("\n");
  }
}

void
depth_first_search (graph_t * graph, adj_node_t * curr, int v)
{
  printf ("visited: %d\n", v);

  if (curr) {
    graph->list[v].visited = TRUE;      // mark the node visited to avoid infinite loops

    while (curr) {      // search all adjacent nodes
      if (!graph->list[curr->vertex].visited) {
        depth_first_search (graph, graph->list[curr->vertex].head,
            curr->vertex);
      }
      curr = curr->next;
    }
  }
}

void
unset_visited (graph_t * graph)
{
  int c;
  for (c = 0; c < graph->num_vertices; c++) {
    graph->list[c].visited = FALSE;
  }
}

int
main ()
{
  printf ("Creating a directed graph: \n");
  graph_t *graph = create_graph (10, DIRECTED);
  add_edge (graph, 0, 2);
  add_edge (graph, 0, 5);
  add_edge (graph, 0, 8);
  add_edge (graph, 1, 6);
  add_edge (graph, 1, 5);
  add_edge (graph, 2, 1);
  add_edge (graph, 2, 3);
  add_edge (graph, 2, 4);
  add_edge (graph, 5, 7);
  add_edge (graph, 5, 9);

  display_graph (*graph);

  printf ("\n");
  depth_first_search (graph, graph->list->head, 0);
}
