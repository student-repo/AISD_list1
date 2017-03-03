#include <stdio.h>

#define MAXQUEUE 100

int queue[MAXQUEUE], first = 0, last = 0;
int push(int element);
int pop();
int getFirst();
int getLast();
int getSize();

int main(){
  printf("%s\n", "size: ");
  printf("%d\n", getSize());
  printf("%s\n","push 19" );
  push(19);

  printf("%s\n", "size: ");
  printf("%d\n", getSize());

  printf("%s\n","push 17" );
  push(19);

  printf("%s\n", "size: ");
  printf("%d\n", getSize());

  printf("%s\n","pop" );
  pop();

  printf("%s\n", "size: ");
  printf("%d\n", getSize());
}

int push(int element){
  if(last == MAXQUEUE){
    return 0;
  }
  queue[last] = element;
  last++;
  return 1;
}

int pop(){
  if(first >= last){
    return 0;
  }
  first++;
  return 1;
}

int getFirst(){
  if(first == last){
    return 0;
  }
  return queue[first];
}


int getLast(){
  if(first == last){
    return 0;
  }
  return queue[last - 1];
}

int getSize(){
  return last - first;
}
