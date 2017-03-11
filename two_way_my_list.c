#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef int Data;
typedef struct Node{
  Data data;
  struct Node *next;
  struct Node *previous;
} Node;
typedef struct list{
  Node *first;
  Node *last;
  int size;
} List;

void initList(List *pq);

bool listEmpty(const List * pq);

Node* getFirst(const List *pq);

Node* getLast(const List *pq);

int listSize(const List *pq);

bool append(Data data, List *pq);

bool removeFirst(List *pq);

bool removeByValue(Data data, List *l);

Node* getNodeByIndex(int index, List *l);

Node* getNodeByValue(Data data, List *l);

void display(List *l);

List* copyList(List *l);

List* merge(List *l1, List *l2);

int main(){
  List l1;
  initList(&l1);
  int i;
  srand(time(NULL));
  for(i = 0; i < 1000; i++){
    int r = rand() % 1000;
    append(r, &l1);
  }
  int randValue = rand() % 1000;
  int foo = getNodeByIndex(randValue, &l1) -> data;
  getNodeByValue(foo, &l1);
  clock_t start = clock();
  getNodeByValue(foo, &l1);
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("repeat acces: %.10e s\n",seconds );

  randValue = rand() % 1000;
  foo = getNodeByIndex(randValue, &l1) -> data;

  start = clock();
  getNodeByValue(foo, &l1);
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("random acces: %.10e s\n",seconds );


  randValue = rand() % 1000;
  foo = getNodeByIndex(randValue, &l1) -> data;
  getNodeByValue(foo, &l1);

  start = clock();
  for(i = 0; i < 1000; i++){
    // getNodeByValue(foo, &l1);
    getNodeByValue(randValue, &l1);
  }
  end = clock();

  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("repeat acces 1000 elements: %.10e s\n",seconds );

  int valuesToCheck[1000];
  for(i = 0; i < 1000; i++){
    randValue = rand() % 1000;
    // valuesToCheck[i] = getNodeByIndex(randValue, &l1) -> data;
    valuesToCheck[i] = randValue;
  }
  start = clock();
  for(i = 0; i < 1000; i++){
    // getNodeByValue(valuesToCheck[i], &l1);
    getNodeByIndex(valuesToCheck[i], &l1);
  }
  end = clock();
  seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("random acces 1000 elements: %.10e s\n",seconds );

  printf("\n");
  printf("%s\n","***" );
  printf("\n");
  printf("%s\n","Testing" );
  printf("\n");

  List l3;
  initList(&l3);
  append(1, &l3);
  append(2, &l3);
  removeByValue(2, &l3);
  append(3, &l3);
  append(4, &l3);
  printf("First list: ");
  display(&l3);
  printf("\n" );

  List l4;
  initList(&l4);
  append(2, &l4);
  append(5, &l4);
  append(6, &l4);
  removeByValue(5, &l4);
  append(7, &l4);
  append(8, &l4);
  printf("Second list: ");
  display(&l4);
  printf("\n" );

  printf("Merge first and second list: " );
  display(merge(&l3, &l4));
  printf("\n");

  printf("First list: ");
  display(&l3);
  printf("\n" );

  printf("Second list: ");
  display(&l4);
  printf("\n" );

  // append(10, &l4);
  display(&l4);
  printf("\n");
  printf("%d\n", getNodeByIndex(3, &l4) -> data  );

}

void initList(List *pq){
  pq -> first = pq -> last = NULL;
  pq -> size = 0;
}

bool listEmpty(const List * pq){
  return pq -> size == 0;
}

Node* getFirst(const List *pq){
  return pq -> first;
}

Node* getLast(const List *pq){
  return pq -> last;
}

int listSize(const List *pq){
  return pq -> size;
}

bool append(Data data, List *pq){
  Node *newNode;
  newNode = (Node *) malloc(sizeof(Node));
  if(newNode == NULL){
    fprintf(stderr, "Memory allocation error!\n");
    exit(1);
  }
  newNode -> data = data;
  newNode -> next = NULL;
  newNode -> previous = pq -> last;
  if(listEmpty(pq)){
    pq -> first = newNode;
  }
  else{
    pq -> last -> next = newNode;
  }
  pq -> last = newNode;
  pq -> size++;
  return true;
}

bool removeFirst(List *pq){
  if(listEmpty(pq)){
    return false;
  }
   Node * pointer = pq -> first;
   pq -> first = pq -> first -> next;
   pq -> first -> previous = NULL;
   free(pointer);
   pq -> size--;
   if(pq -> size == 0){
     pq -> last = NULL;
   }
   return true;
}

bool removeByValue(Data data, List *l){
  Node *current = l -> first;
  Node *toRemove = NULL;
  if(current -> data == data){
    removeFirst(l);
  }
  while(current -> next != NULL){
    if(current -> data == data){
      current -> previous -> next = current -> next;
      current -> next -> previous = current -> previous;
      break;
    }
    current = current -> next;
  }
  if((current -> data == data) && (current -> next == NULL)){
    current -> previous -> next = NULL;
    l -> last = current -> previous;
  }
  else if(current -> next == NULL){
    return false;
  }
  free(current);
  l -> size--;
  return true;
}

Node* getNodeByIndex(int index, List *l){
  int i;
  Node *n;
  int k = listSize(l);
  if(((int)(k / 2) >= index)){
    n = l -> first;
    for(i = 0; i < index; i++){
        n = n -> next;
    }
  }
  else{
    n = l -> last;
    for(i = (k - index - 1); i > 0; i--){
        n = n -> previous;
    }
  }

  // n = l -> first;
  // for(i = 0; i < index; i++){
  //     n = n -> next;
  // }

  return n;
}

Node* getNodeByValue(Data data, List *l){
  Node *current = l -> first;
  if(current -> data == data){
    return current;
  }
  while(current -> next != NULL){
    if(data == current -> data){
      current -> previous -> next = current -> next;
      current -> next -> previous = current -> previous;
      l -> first -> previous = current;
      current -> next = l -> first;
      current -> previous = NULL;
      l -> first = current;
      return current;
    }
    current = current -> next;
  }
  if(current -> data == data){
    current -> previous -> next = current -> next;
    current -> next = l -> first;
    l -> first = current;
    l -> last = current -> previous;

    return current;
  }
  return NULL;
}

void display(List *l){
  Node *node = l -> first;
  printf("[");
  int i, listLength = listSize(l);
  for(i = 0; i < listLength; i++){
    printf("%d ,", node -> data);
    // printf("%p,",node );
    node = node -> next;
  }
  printf("]");
}

List* copyList(List *l){
  List *newList;
  newList = (List *) malloc(sizeof(List));
  if(l -> size == 0){
    initList(newList);
    return newList;
  }
  newList -> size = l -> size;
  int i, listLength = listSize(l);
  Node *current = l -> first;
  Node *previous = NULL;
  for(i = 0; i < listLength; i++){
    Node *b;
    b = (Node *) malloc(sizeof(Node));
    b -> data = current -> data;
    b -> next = NULL;
    b -> previous = previous;
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
  if(l1 -> size == 0){
    return l2;
  }
  else if(l2 -> size == 0){
    return l1;
  }
  List *ll1 = copyList(l1);
  List *ll2 = copyList(l2);
  ll1 -> last -> next = ll2 -> first;
  ll1 -> last -> next -> previous = ll1 -> last;
  ll1 -> size = ll1 -> size + ll2 -> size;
  ll1 -> last = ll2 -> last;
  return ll1;
}
