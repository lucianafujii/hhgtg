/* Implement a single linked list */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  struct node *next;
  int n;
} node;

typedef enum
{
  FALSE, TRUE
} bool;

bool
insert_prepend (node ** l, int n) /* Insert at beginning of the list */
{
  printf ("insert prepend %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  if (!new_node)
    return FALSE;

  new_node->n = n;
  new_node->next = *l;
  *l = new_node;

  return TRUE;
}

bool
insert_append (node ** l, int n) /* Insert at end of the list */
{
  printf ("insert append %d\n", n);

  node *new_node = (node *) malloc (sizeof (node));
  if (!new_node)
    return FALSE;

  new_node->n = n;
  new_node->next = NULL;

  if (*l) {
    node *current = *l;
    while (current->next) {
      current = current->next;
    }
    current->next = new_node;
  } else {
    *l = new_node;
  }

  return TRUE;
}

bool
dequeue (node ** l, int *value)
{                               /* retrieve and remove the first item */
  if (*l) {
    *value = (*l)->n;

    node *tmp = *l;        // pointer to first node
    *l = tmp->next;
    free (tmp);

    return TRUE;
  } else {
    printf ("list is empty\n");
    return FALSE;
  }
}

bool
pop (node ** l, int *value)
{                               /* retrieve and remove the last item */
  if (!*l) {
    printf ("list is empty\n");
    return FALSE;
  }

  node *runner = *l;

  if (!runner->next) { // only one element in the list
    *value = runner->n;
    free (runner);
    *l = NULL;
  } else {
    while (runner->next->next) { // make runner second to last element
      runner = runner->next;
    }

    *value = runner->next->n;
    free (runner->next);
    runner->next = NULL;
  }

  return TRUE;
}

bool
travel (node * l)
{
  node *tmp = l;

  printf ("the list contains: ");
  while (tmp) {
    printf ("%d ", tmp->n);

    tmp = tmp->next;
  }
  printf ("\n\n");

  return TRUE;
}

bool
remove_node (node ** l, int n)
{
  if (*l) {             // not an empty list
    node *head = *l;

    if (head->n == n) {         // if first node
      *l = head->next;          // list points to the second
      free (head);
    } else {
      while (head->next->n != n) {      // find node
        if (!head->next->next)   // node isn't in the list
          return FALSE;

        head = head->next;
      }

      node *tmp = head->next->next;
      free (head->next);
      head->next = tmp;         // make previous node point to next
    }
  }

  return TRUE;
}

bool
reverse_order (struct node **head)
{
  struct node *new_head = NULL;

  while (*head) {
    struct node *tmp = *head;
    *head = (*head)->next;
    tmp->next = new_head;
    new_head = tmp;
  }

  *head = new_head;

  return TRUE;
}

int
main ()
{
  // start with an empty list
  node *list = NULL;
  int n;
  travel (list);

  // add a few elements to the list
  insert_append (&list, 2);
  insert_append (&list, 3);
  insert_prepend (&list, 1);
  insert_prepend (&list, 0);
  insert_append (&list, 4);
  insert_append (&list, 5);
  insert_append (&list, 6);

  // travel the list
  travel (list);

  // remove all elements
  dequeue (&list, &n);
  printf ("remove first item: %d\n", n);
  dequeue (&list, &n);
  printf ("remove first item: %d\n", n);
  travel (list);

  // reverse order of list
  printf ("reverse order of list\n");
  reverse_order (&list);
  travel (list);

  printf ("remove item with value 3\n");
  remove_node (&list, 3);
  travel (list);

  printf ("remove item with value 2\n");
  remove_node (&list, 2);
  travel (list);

  printf ("remove item with value 7\n");
  remove_node (&list, 7);
  travel (list);

  pop (&list, &n);
  printf ("remove last item: %d\n", n);
  pop (&list, &n);
  printf ("remove last item: %d\n", n);
  dequeue (&list, &n);
  printf ("remove first item: %d\n", n);

  if (pop (&list, &n))
    printf ("remove last item: %d\n", n);
}
