#include<stdio.h>

int main(){
  int size=0;
  struct node{
    int data;
    struct node* next;
  };
  struct node* DUMMY;
  struct node NODE;
  DUMMY=(struct node*)malloc(sizeof(struct node));
  //NODE.data=0;
  DUMMY=&NODE;
  for(size=1;size<10;size++){
    DUMMY->data=size;
    DUMMY=DUMMY->next;

  }
  DUMMY=&NODE;
  size=1;
  for(size=1;size<10;size++){
    printf("%d",DUMMY->data);
    DUMMY=DUMMY->next;
  }
}
