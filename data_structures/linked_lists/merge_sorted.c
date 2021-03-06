/*
 * Merge two sorted lists A and B as one linked list
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
  int data;
  struct Node *next;
} Node;

typedef enum
{
  FALSE, TRUE
} bool;


Node
Append (Node ** head, int data)
{
  //printf ("Append: %d\n", data);
  Node *new_node = (Node *) malloc (sizeof (Node));
  new_node->data = data;
  new_node->next = NULL;

  Node *run = *head;
  if (run) {                    // go to last element and insert after it
    while (run->next)
      run = run->next;

    run->next = new_node;
  } else {                      // empty list, new node is head
    *head = new_node;
  }
}

Node *
MergeLists (Node * headA, Node * headB)
{
  Node *tmp = (Node *) malloc (sizeof (Node));
  tmp = NULL;

  while (headA && headB) {      // run through both lists until one is empty
    if (headA->data < headB->data) {    // appending the smallest new head
      Append (&tmp, headA->data);
      headA = headA->next;
    } else {
      Append (&tmp, headB->data);
      headB = headB->next;
    }
  }

  while (headA) {               // one of the two lists isn't empty yet
    Append (&tmp, headA->data);
    headA = headA->next;
  }
  while (headB) {
    Append (&tmp, headB->data);
    headB = headB->next;
  }

  return tmp;
}

void
Print (Node * head)
{
  bool ok = FALSE;
  while (head != NULL) {
    printf ("%d ", head->data);
    head = head->next;
  }
  printf ("\n");
}

Node *
Insert (Node * head, int x)
{
  Node *tmp = (Node *) malloc (sizeof (Node));
  tmp->data = x;
  tmp->next = NULL;

  if (head == NULL) {
    return tmp;
  }

  Node *tmp1 = head;
  while (tmp1->next != NULL)
    tmp1 = tmp1->next;

  tmp1->next = tmp;
  return head;
}


int
main ()
{
  Node *A = NULL;
  Node *B = NULL;

  A = Insert (A, 0);
  A = Insert (A, 3);
  A = Insert (A, 5);
  A = Insert (A, 6);
  A = Insert (A, 7);
  A = Insert (A, 8);

  B = Insert (B, 1);
  B = Insert (B, 2);
  B = Insert (B, 3);
  B = Insert (B, 4);
  B = Insert (B, 5);
  B = Insert (B, 6);
  B = Insert (B, 7);
  B = Insert (B, 8);
  B = Insert (B, 9);

  Print (A);
  Print (B);

  A = MergeLists (A, B);
  Print (A);
}
