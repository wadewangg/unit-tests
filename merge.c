#include<stdio.h>
#include<stdlib.h>
  
/* Link list node */
typedef struct List_node
{
    int value;
    struct List_node *next;
} List;
 
/* function prototypes */
void MergeSort(List **headRef);
List *SortedMerge(List *a, List *b);
void FrontBackSplit(List *source,
          List **frontRef, List **backRef);
 
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(List **headRef)
{
  List *head = *headRef;
  List *a=NULL;
  List *b=NULL;
 
  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b); 
 
  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);
 
  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this 
   function */
List *SortedMerge(List* a, List* b)
{
  List *result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return b;
  else if (b==NULL)
     return a;
 
  /* Pick either a or b, and recur */
  if (a->value <= b->value)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return result;
}
 
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra node should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(List *source,
          List **frontRef, List **backRef)
{
  List *fast=NULL;
  List *slow=NULL;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
 

  
