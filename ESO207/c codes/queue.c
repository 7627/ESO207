#include<stdio.h>
#include<stdlib.h>
struct node{
  int val;
  // struct node* prev;
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
  struct node* queue=NULL;
  // queue=calloc(1,sizeof(struct node));
  // queue->val=1;
  int testcases,q,opcode,val;
  scanf("%d",&testcases);
  int i=0;
  for(i=0;i<testcases;i++){
    queue=NULL;
    scanf("%d",&q);
    int j=0;
    for(j=0;j<q;j++){
      scanf("%d",&opcode);
        switch(opcode){
          case 1:
            scanf("%d",&val);
            queue=enqueue(queue,val);
            break;
          case 2:
            queue=dequeue(queue);
            break;
          case 3:
            isEmpty(queue);
            break;
          default:
            printf("Invalid opcode\n");
            break;
        }
    }
  }
  // for(struct node*temp=queue;temp!=NULL;temp=temp->next){
  //   printf("let me print the queue %d\n",temp->val);
  return 0;

}
