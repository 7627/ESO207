#include<stdio.h>
#include<stdlib.h>
struct node{
  int val;
  struct node* next;
};

int isEmpty(struct node* queue){
  if(queue==NULL){
    printf("True\n");
    return 1;
  }
  printf("False\n");
  return 0;
}

struct node* enqueue(struct node* queue, int val){
  struct node* temp=queue;
  if(queue==NULL){
    queue=calloc(1,sizeof(struct node));
    queue->val=val;
    printf("%d\n",val);
    return queue;
  }
  while(queue->next!=NULL){
    queue=queue->next;
  }
  queue->next=calloc(1,sizeof(struct node));
  queue->next->val=val;
  printf("%d\n",val);
  return temp;
}
struct node* dequeue(struct node* queue){
  struct node* temp=queue;
  if(queue==NULL){
    printf("Empty\n");
    return queue;
  }
  printf("%d\n",queue->val);
  queue=queue->next;
  free(temp);
  return queue;
}

int main(){
  int testcases,seq_size,q;
  struct node** sequence=NULL;
  /*sequence=calloc(3,sizeof(struct node*));
  enqueue(sequence[1],6);
  isEmpty(sequence[2]);
  enqueue(sequence[2],7);
  isEmpty(sequence[2]);
  dequeue(sequence[0]);
  dequeue(sequence[2]);
  printf("%d",sequence[1]==NULL);*/
  scanf("%d",&testcases);
  int i=0,j=0,opcode,x,index;
  for(i=0;i<testcases;i++){
    sequence=NULL;
    scanf("%d %d",&seq_size,&q);
    sequence=calloc(seq_size,sizeof(struct node*));
    for(int k=0;k<seq_size;k++){
      sequence[k]=NULL;
    }
    for(j=0;j<q;j++){
      scanf("%d",&opcode);
      switch(opcode){
        case 1:
          scanf("%d %d",&x,&index);
          sequence[index-1]=enqueue(sequence[index-1],x);
          break;
        case 2:
          scanf("%d",&index);
          sequence[index-1]=dequeue(sequence[index-1]);
          break;
        case 3:
          scanf("%d",&index);
          isEmpty(sequence[index-1]);
          break;
        default:
          printf("Invalid opcode");
          break;
      }
    }
    for(int y=0;y<seq_size;y++){
      free(sequence[y]);
    }
    free(sequence);
  }

  return 0;
}
