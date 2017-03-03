#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Item;
#define MAXQUEUE 10
typedef struct Node{
  Item item;
  struct Node *next;
} Node;
typedef struct queue{
  Node *front;
  Node *back;
  int item;
} Queue;

static void copyToItem(Node *pn, Item *item);
void initQueue(Queue *pq){
  pq -> front = pq -> back = NULL;
  pq -> item = 0;
}

bool queueFull(const Queue *pq){
  return pq -> item == MAXQUEUE;
}

bool queueEmpty(const Queue * pq){
  return pq -> item == 0;
}

Item getFirst(const Queue *pq){
  return pq -> front -> item;
}

Item getLast(const Queue *pq){
  return pq -> back -> item;
}

int itemAmount(const Queue *pq){
  return pq -> item;
}

bool push(Item item, Queue *pq){
  Node *newNode;
  if(queueFull(pq)){
    return false;
  }
  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL){
    fprintf(stderr, "Memory allocation error!\n");
    exit(1);
  }
  newNode -> item = item;
  newNode -> next = NULL;
  if(queueEmpty(pq)){
    pq -> front = newNode;
  }
  else{
    pq -> back -> next = newNode;
  }
  pq -> back = newNode;
  pq -> item++;
  return true;
}

bool pop(Queue *pq){
  if(queueEmpty(pq)){
    return false;
  }
   Node * pointer = pq -> front;
   pq -> front = pq -> front -> next;
   free(pointer);
   pq -> item--;
   if(pq -> item == 0){
     pq -> back = NULL;
   }
   return true;
}
// bool pop(Queue *pq){
//    Node * pointer;
//    if(queueEmpty(pq)){
//      return false;
//    }
//    pointer = pq -> front -> next;
//    free(pointer);
//    pq -> item--;
//    if(pq -> item == 0){
//      pq -> back = NULL;
//    }
//    return true;
// }

static void copyToItem(Node * pn, Item *pi){
  *pi = pn -> item;
}
int main(){
  Queue kol;
  Item tymcz;
  initQueue(&kol);
  push('a', &kol);
  push('b', &kol);
  push('c', &kol);
  push('d', &kol);
  pop(&kol);
  push('f', &kol);
  printf("%d\n",itemAmount(&kol) );
  printf("%c\n",getFirst(&kol) );
  printf("%c\n",getLast(&kol) );
}
