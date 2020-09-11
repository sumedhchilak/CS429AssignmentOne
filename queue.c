/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q;
    q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL){
      return NULL;
    } else {
    // Initialize all references to null and set size as 0
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
    }
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    // Only free q when it is not null
    if(q != NULL){
      list_ele_t *temp;
      while(q->head != NULL){
        // store the next reference in temp
        temp = q->head->next;
        free(q->head->value);
        free(q->head);
        // set temp back to head which is the next reference and traverse through
        q->head = temp;
      }
      free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    /* What should you do if the q is NULL? */
    if(q == NULL){
      return false;
    }
    // Allocate space of appropriate size
    newh = malloc(sizeof(list_ele_t));
   if(newh == NULL){
      return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    // Add one for the null/0 at the end
    size_t length = strlen(s) + 1;
    // Allocate the space which for char and the length of string plus the null
    newh->value = malloc(length*sizeof(char));
    /* What if either call to malloc returns NULL? */
    if(newh->value == NULL){
      free(newh);
      return false;
    }
    strcpy(newh->value, s);
    newh->next = q->head;
    q->head = newh;
    if(q->size == 0){
      q->tail = newh;
    }
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if(q == NULL){
      return false;
    }
    list_ele_t *newTail;
    newTail = malloc(sizeof(list_ele_t));
    if(newTail == NULL){
      return false;
    }
    // get string length plus 1 for the null at the end
    size_t length = strlen(s) + 1;
    newTail->value = malloc(length*sizeof(char));
    // if malloc returns null then free the space for newTail
    if(newTail->value == NULL){
      free(newTail);
      return false;
    }
    strcpy(newTail->value, s);
    if(q->size == 0){
      q->head = newTail;
    } else{
      q->tail->next = newTail;
    }
    q->tail = newTail;
    newTail->next = NULL;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    // Edge cases to make sure the buffsize is atleast 2 and q or q->head are not null
    if(bufsize < 1 || q == NULL || q->head == NULL){
      return false;
    }
    if(sp != NULL){
      strncpy(sp, q->head->value, bufsize - 1);
      // Set the end to the null/0
      sp[bufsize - 1] = (char) 0;
    }
    /* You need to fix up this code. */
    list_ele_t *newHeader = q->head->next;
    // Free both spaces
    free(q->head->value);
    free(q->head);
    q->head = newHeader;
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if(q != NULL && q->head != NULL){
      return q->size;
    }
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if(q != NULL && q->size > 1){
      list_ele_t *previous = NULL;
      list_ele_t *current = q->head;
      list_ele_t *next;
      q->tail = q->head;
      while(current != NULL){
        next = current->next;
        // Changes the reference direction to point the other way
        current->next = previous;
        // previous holds the prior node
        previous = current;
        // current goes to the next one
        current = next;
      }
      // Make sure the head direction set to previous
      q->head = previous;
    }

}

