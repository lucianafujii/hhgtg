/* Write code to partition a linked list around a value x, such that all nodes */
/* less than x come before all nodes greater than or equal to x.               */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  int d;
  struct node *next;
} node;


void
travel (node * l)
{
  while (l) {
    printf ("%d ", l->d);
    l = l->next;
  }
  printf ("\n");
}

void
prepend (node ** l, int d)
{
  node *new = (node *) malloc (sizeof (node));
  new->d = d;
  new->next = *l;
  *l = new;
}

void
partition (node ** l, int middle)
{
  node *lower = NULL;
  node *higher = NULL;
  node *tmp = NULL;
  node *head = *l;

  while (head) {
    if (head->d < middle)
      prepend (&lower, head->d);
    else
      prepend (&higher, head->d);

    tmp = head;
    head = head->next;
    free (tmp);
  }

  head = lower;
  if (!head)
    *l = higher;
  else {
    while (head->next) {
      head = head->next;
    }
    head->next = higher;
    *l = lower;
  }
}

/* partition without creating new nodes and freeing the old */
void
partition_directly (node ** l, int middle)
{
  node *lower = NULL;
  node *higher = NULL;
  node *head = *l;
  node *next = NULL;

  /* Partition list */
  while (head) {
    next = head->next;
    if (head->d < middle) {
      /* Insert node into start of lower list */
      head->next = lower;
      lower = head;
    } else {
      /* Insert node into fron of after list */
      head->next = higher;
      higher = head;
    }
    head = next;
  }

  /* Merge lower and higher lists */
  if (!lower)
    *l = higher;
  else {
    *l = lower;
    while (lower->next) {
      lower = lower->next;
    }
    lower->next = higher;
  }
}


int
main ()
{
  node *l = NULL;
  prepend (&l, 9);
  prepend (&l, 7);
  prepend (&l, 5);
  prepend (&l, 3);
  prepend (&l, 1);
  prepend (&l, 8);
  prepend (&l, 6);
  prepend (&l, 4);
  prepend (&l, 2);

  travel (l);

  printf ("All numbers below 5 to the left: ");
  partition_directly (&l, 5);
  travel (l);
}
