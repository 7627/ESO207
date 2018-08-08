#include<stdio.h>
#include<stdlib.h>
struct node{
  int data;
  struct node* next;
};
void print_list(struct node* head){
  struct node* temp=head;
  while(temp!=NULL){
    printf("%d",temp->data);
    temp=temp->next;
  }
}
struct node* make_node(int val){
  struct node* tmp;
  tmp=calloc(1,sizeof(struct node));
  tmp->data=val;
  return tmp;
}
struct node* insert_at_front(struct node* head,int x){
  struct node* temp;
  temp=calloc(1,sizeof(struct node));
  temp->data=x;
  temp->next=head;
  head=temp;
  return head;
}
struct node* search(struct node* head,int val){
  struct node *tmp;
  tmp=head;
  while(tmp->next!=NULL){
    if(tmp->data==val){
      break;
    }
    tmp=tmp->next;
  }
  return tmp;
}
void insert_after(struct node* head,int after,int val){
  struct node *tmp1=make_node(val);
  struct node *tmp2=search(head,after);
  tmp1->next=tmp2->next;
  tmp2->next=tmp1;
}
void delete_after(struct node* head,int del_after){
  struct node* tmp=search(head,del_after);
  struct node* tmp2=tmp->next;
  tmp->next=tmp->next->next;
  free(tmp2);
}
int main(){
  struct node* head=calloc(1,sizeof(struct node));
  head->data=0;
  head=insert_at_front(insert_at_front(insert_at_front(insert_at_front(head,1),2),3),4);
  print_list(head);
  printf(" Search Result=%d ",search(head,1)->data);
  insert_after(head,3,9);
  print_list(head);
  printf(" ");
  delete_after(head,3);
  print_list(head);
}
