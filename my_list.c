#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Item;
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

Item getFirst(const List *pq){
  return pq -> first -> item;
}

Item getLast(const List *pq){
  return pq -> last -> item;
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
  Node *toRemove;
  if(current -> item == item){
    removeFirst(l);
  }
  while(current -> next != NULL){
    if(item == current -> next -> item){
      toRemove = current -> next;
      break;
    }
    current = current -> next;
  }
  if(current -> next == NULL){
    return false;
  }
  current -> next = current -> next -> next;
  free(toRemove);
  l -> item--;
  return true;
}

Node* getNodeByValue(Item item, List *l){
  Node *current = l -> first;
  if(current -> item == item){
    return current;
  }
  else if(l -> last -> item == item){
    return l -> last;
  }
  while(current -> next != NULL){
    if(item == current -> item){
      return current;
    }
    current = current -> next;
  }
  return NULL;
}

void display(List *l){
  Node *node = l -> first;
  printf("[");
  int i, listLength = itemAmount(l);
  for(i = 0; i < listLength; i++){
    printf("%c ,", node -> item);
    // printf("%p,",node );
    node = node -> next;
  }
  printf("]");
}

List* copyList(List *l){
  List *newList;
  newList = (List *) malloc(sizeof(List));
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
    else if(i == (listLength -1)){
      newList -> last = b;
    }
    previous = b;
    current = current -> next;
  }
  return newList;
}

List* merge(List *l1, List *l2){
  List *ll1 = copyList(l1);
  List *ll2 = copyList(l2);
  ll1 -> last -> next = ll2 -> first;
  ll1 -> item = ll1 -> item + ll2 -> item;
  ll1 -> last = ll2 -> last;
  return ll1;
}


int main(){
  List l1;
  Item tymcz;
  initList(&l1);
  append('a', &l1);
  append('b', &l1);
  append('c', &l1);
  append('d', &l1);
  removeFirst(&l1);
  append('f', &l1);
  printf("%d\n",itemAmount(&l1) );
  printf("%c\n",getFirst(&l1) );
  printf("%c\n",getLast(&l1) );
  removeByValue('b', &l1);
  printf("%s\n","before removing" );
  display(&l1);
  Node *a = getNodeByValue('f', &l1);
  printf("%c\n",a -> item );

  List l2;
  initList(&l2);
  append('z', &l2);
  append('x', &l2);
  append('y', &l2);
  append('w', &l2);
  removeFirst(&l2);
  display(&l2);

  // List *l3 = copyList(&l1);
  List *l3 = merge(&l1, &l2);
  // printf("\n" );
  // printf("\n" );
  removeByValue('d', &l1);
  removeByValue('f', &l1);
  removeByValue('x', &l2);
  removeByValue('w', &l2);
  display(l3);
  printf("%s\n","after remove" );
  display(&l1);
  display(&l2);

  // display(&l1);
  // List *l3 = merge(&l1, &l2);
  // display(l3);
  //
  //
  // Node *b;
  // b = (Node *) malloc(sizeof(Node));
  // b = l3 -> first;
  // while(b -> next != NULL){
  //   printf("%c\n",b -> item );
  //   b = b -> next;
  // }

}
