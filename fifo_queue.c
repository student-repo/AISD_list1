#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;
#define MAXQUEUE 10
typedef struct Node{
  Data data;
  struct Node * next;
} Node;

typedef struct Queue{
  Node * front;
  Node * back;
  int size;
} Queue;

void initQueue(Queue *q);

Data getFirst(const Queue *q);

Data getLast(const Queue *q);

bool fullQueue(const Queue *q);

bool emptyQueue(const Queue *q);

int getSize(const Queue *q);

bool push(Data data, Queue *q);

bool pop(Queue *q);

int main(){
  Queue q;
  initQueue(&q);
  push(1, &q);
  push(2, &q);
  push(3, &q);
  push(4, &q);
  push(5, &q);
  push(6, &q);
  push(7, &q);
  push(8, &q);
  push(9, &q);
  push(10, &q);
  pop(&q);
  pop(&q);
  pop(&q);
  pop(&q);
  printf("%d\n",getSize(&q) );

  printf("First = %d\n",getFirst(&q) );
  printf("Last = %d\n", getLast(&q) );
}

void initQueue(Queue *q){
  q -> front = q -> back = NULL;
  q -> size = 0;
}

Data getFirst(const Queue *q){
  return q -> front -> data;
}

Data getLast(const Queue *q){
  return q -> back -> data;
}

bool fullQueue(const Queue *q){
  return q -> size == MAXQUEUE;
}

bool emptyQueue(const Queue *q){
  return q -> size == 0;
}

int getSize(const Queue *q){
  return q -> size;
}



bool push(Data data, Queue *q){
  Node * newNode;
  if(fullQueue(q)){
    return false;
  }
  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL){
    fprintf(stderr, "Memory allocation error!\n");
    exit(1);
  }
  newNode -> data = data;
  newNode -> next = NULL;
  if(emptyQueue(q)){
    q -> front = newNode;
  }
  else{
    q -> back -> next = newNode;
  }
  q -> back = newNode;
  q -> size++;
  return true;
}
bool pop(Queue *q){
   Node *toRemove;
   if(emptyQueue(q)){
     return false;
   }
   toRemove = q -> front;
   q -> front = q -> front -> next;
   free(toRemove);
   q -> size--;
   if(q -> size == 0){
     q -> back = NULL;
   }
   return true;
}
