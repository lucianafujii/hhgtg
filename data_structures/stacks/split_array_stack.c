/* Use a single array to implement three stacks */

#include <stdio.h>

typedef enum
{ FALSE, TRUE } bool;

int stackSize = 100;
int buffer[300];                // stackSize * 3
int stackPointer[] = { -1, -1, -1 };    // pointers to track top elements

/* returns index of top of stack "stackNum", in absolute terms */
int
absTopOfStack (int stackNum)
{
  return stackNum * stackSize + stackPointer[stackNum];
}

void
push (int stackNum, int value)
{
  /* Check if we have space */
  if (stackPointer[stackNum] + 1 >= stackSize) {        // Last element
    return;
  }

  /*Increment stack pointer and then update top value */
  stackPointer[stackNum]++;
  buffer[absTopOfStack (stackNum)] = value;
}

int
pop (int stackNum)
{
  if (stackPointer[stackNum] == -1) {
    return -1;                  // Trying to pop an empty stack
  }

  int value = buffer[absTopOfStack (stackNum)]; // Get top
  buffer[absTopOfStack (stackNum)] = 0; // clear index
  stackPointer[stackNum]--;     // Decrement pointer
  return value;
}

int
peek (int stackNum)
{
  int index = absTopOfStack (stackNum);
  return buffer[index];
}

bool
isEmpty (int stackNum)
{
  return stackPointer[stackNum] == -1;
}


int
main ()
{
  printf ("push to %d: %d\n", 0, 1);
  push (0, 1);
  printf ("push to %d: %d\n", 0, 2);
  push (0, 2);
  printf ("push to %d: %d\n", 0, 3);
  push (0, 3);
  printf ("\n");

  printf ("push to %d: %d\n", 1, 4);
  push (1, 4);
  printf ("push to %d: %d\n", 1, 8);
  push (1, 8);
  printf ("push to %d: %d\n", 1, 16);
  push (1, 16);
  printf ("push to %d: %d\n", 1, 32);
  push (1, 32);
  printf ("\n");

  printf ("push to %d: %d\n", 2, 20);
  push (2, 20);
  printf ("push to %d: %d\n", 2, 40);
  push (2, 40);
  printf ("push to %d: %d\n", 2, 60);
  push (2, 60);
  printf ("\n");

  printf ("pop from %d: %d\n", 0, pop (0));
  printf ("pop from %d: %d\n", 0, pop (0));
  printf ("pop from %d: %d\n", 0, pop (0));
  printf ("\n");

  printf ("pop from %d: %d\n", 1, pop (1));
  printf ("pop from %d: %d\n", 1, pop (1));
  printf ("pop from %d: %d\n", 1, pop (1));
  printf ("pop from %d: %d\n", 1, pop (1));
  printf ("pop from %d: %d\n", 1, pop (1));
  printf ("\n");

  printf ("pop from %d: %d\n", 2, pop (2));
  printf ("push to %d: %d\n", 2, 100);
  push (2, 100);
  printf ("push to %d: %d\n", 2, 200);
  push (2, 200);
  printf ("pop from %d: %d\n", 2, pop (2));
  printf ("pop from %d: %d\n", 2, pop (2));
  printf ("pop from %d: %d\n", 2, pop (2));
  printf ("pop from %d: %d\n", 2, pop (2));
}
