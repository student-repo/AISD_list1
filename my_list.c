#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int Item;
typedef struct Node{
  Item item;
  struct Node *next;
} Node;
typedef struct list{
  Node *first;
  Node *last;
  int item;
} List;

void initList(List *pq){
  pq -> first = pq -> last = NULL;
  pq -> item = 0;
}

bool listEmpty(const List * pq){
  return pq -> item == 0;
}

Node* getFirst(const List *pq){
  return pq -> first;
}

Node* getLast(const List *pq){
  return pq -> last;
}

int itemAmount(const List *pq){
  return pq -> item;
}

bool append(Item item, List *pq){
  Node *newNode;
  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL){
    fprintf(stderr, "Memory allocation error!\n");
    exit(1);
  }
  newNode -> item = item;
  newNode -> next = NULL;
  if(listEmpty(pq)){
    pq -> first = newNode;
  }
  else{
    pq -> last -> next = newNode;
  }
  pq -> last = newNode;
  pq -> item++;
  return true;
}

bool removeFirst(List *pq){
  if(listEmpty(pq)){
    return false;
  }
   Node * pointer = pq -> first;
   pq -> first = pq -> first -> next;
   free(pointer);
   pq -> item--;
   if(pq -> item == 0){
     pq -> last = NULL;
   }
   return true;
}

bool removeByValue(Item item, List *l){
  Node *current = l -> first;
  Node *toRemove = NULL;
  if(current -> item == item){
    removeFirst(l);
  }
  int i, listLength = l -> item;
  for(int i = 0; i < listLength; i++){
    if(item == current -> next -> item){
      if(i == listLength -2){
        l -> last = current;
      }
      toRemove = current -> next;
      break;
    }
    current = current -> next;
  }
  if(toRemove == NULL){
    return false;
  }
  current -> next = current -> next -> next;
  free(toRemove);
  l -> item--;
  return true;
}

Node* getNodeByIndex(int index, List *l){
  int i;
  Node *n;
  n = l -> first;
  for(int i = 0; i < index; i++){
      n = n -> next;
  }
  return n;
}

Node* getNodeByValue(Item item, List *l){
  Node *current = l -> first;
  Node *previous = NULL;
  if(current -> item == item){
    return current;
  }
  while(current -> next != NULL){
    if(item == current -> item){
      previous -> next = current -> next;
      current -> next = l -> first;
      l -> first = current;
      return current;
    }
    previous = current;
    current = current -> next;
  }
  if(current -> item == item){
    previous -> next = current -> next;
    current -> next = l -> first;
    l -> first = current;
    l -> last = previous;
    return current;
  }
  return NULL;
}

void display(List *l){
  Node *node = l -> first;
  printf("[");
  int i, listLength = itemAmount(l);
  for(i = 0; i < listLength; i++){
    printf("%d ,", node -> item);
    // printf("%p,",node );
    node = node -> next;
  }
  printf("]");
}

List* copyList(List *l){
  List *newList;
  newList = (List *) malloc(sizeof(List));
  if(l -> item == 0){
    initList(newList);
    return newList;
  }
  newList -> item = l -> item;
  int i, listLength = itemAmount(l);
  Node *current = l -> first;
  Node *previous = NULL;
  for(i = 0; i < listLength; i++){
    Node *b;
    b = (Node *) malloc(sizeof(Node));
    b -> item = current -> item;
    b -> next = NULL;
    if(previous != NULL){
      previous -> next = b;
    }
    if(i == 0){
      newList -> first = b;
    }
    if(i == (listLength -1)){
      newList -> last = b;
    }
    previous = b;
    current = current -> next;
  }
  return newList;
}

List* merge(List *l1, List *l2){
  if(l1 -> item == 0){
    return l2;
  }
  else if(l2 -> item == 0){
    return l1;
  }
  List *ll1 = copyList(l1);
  List *ll2 = copyList(l2);
  ll1 -> last -> next = ll2 -> first;
  ll1 -> item = ll1 -> item + ll2 -> item;
  ll1 -> last = ll2 -> last;
  return ll1;
}


int main(){
  List l1;
  initList(&l1);
  int i;
  srand(time(NULL));
  // clock_t start = clock();
  for(i = 0; i < 1000; i++){
    int r = rand() % 1000;
    // printf("%d\n",r );
    append(r, &l1);
  }
  // clock_t end = clock();
  // double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  // display(&l1);
  // printf("\n" );
  // printf("%f\n", seconds);
  int randValue = rand() % 1000;
  int foo = getNodeByIndex(randValue, &l1) -> item;
  // printf("%d\n",foo);
  getNodeByValue(foo, &l1);
  // display(&l1);
  clock_t start = clock();
  getNodeByValue(foo, &l1);
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("%f\n",seconds );

  randValue = rand() % 1000;
  start = clock();
  getNodeByIndex(randValue, &l1);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("%f\n",seconds );

}
