#include<iostream>
using namespace std;

struct node{
  int val;
  struct node* next;
};

void change(struct node* root,int j){
  static int i=0;
  i=i+1;
  cout<<i<<endl;
  root->val=j;
}
int main(){
  struct node* root=(struct node*)calloc(1,sizeof(struct node));
  root->val=1;
  root->next=(struct node*)calloc(1,sizeof(struct node));
  root->next->val=2;
  root->next->next=(struct node*)calloc(1,sizeof(struct node));
  root->next->next->val=3;
  // cout<<root->val<<endl;
  change(root,4);
  change(root,5);
  root->next=NULL;
  cout<<(root->next==NULL)<<endl;
  cout<<root->next->val<<endl;
  // cout<<root->val<<endl;
}
