#include<iostream>
#include<stdlib.h>
using namespace std;

struct node{
  string str;
  int rank;
  struct node* parent;
  struct node*left;
  struct node*right;
};
typedef struct node Node;

Node* createNode(string str){
  Node* tmp=(Node*)calloc(1,sizeof(Node));
  tmp->str=str;
  return tmp;
}

Node* insertNode(Node*root,string str){
  Node*tmp=root;
  if(root==NULL){
    root=createNode(str);
    return root;
  }
  while(root!=NULL){
    if(str==root->str){
      // cout<<"already present";
      return tmp;
    }
    if(str<root->str){
      if(root->left==NULL){
        root->left=createNode(str);
        root->left->parent=root;
        return tmp;
      }
      else{
        root=root->left;
      }
    }
    else{
      if(root->right==NULL){
        root->right=createNode(str);
        root->right->parent=root;
        return tmp;
      }
      root=root->right;
    }
  }
}

Node* find(Node* root,string str){
  if(root==NULL){
    return root;
  }
  // if(root->str==str){
  //   return root;
  // }
  while(root->str!=str && root!=NULL){
    if(str<root->str){
      root=root->left;
    }
    else{
      root=root->right;
    }
  }
  return root;
}

Node* succ(Node* root){
  root=root->right;
  // cout<<"yoyoo"<<endl;
  while(root->left!=NULL){
    // cout<<root->str<<endl;
    root=root->left;
  }
  return root;
}


void del(Node** root, Node* delete_it,int flag){
  // Node* root=root;
  Node* tmp=delete_it;
  // cout<<"delete_it : "<<tmp->str<<endl;
  if(flag==0) cout<<tmp->rank<<endl;
  if(tmp->left==NULL){
    // cout<<"left==NULL"<<endl;
    if(tmp->parent==NULL){
      // cout<<"parent==NULL"<<endl;
      // cout<<"root= "<<(*root)->str<<endl;
      if(tmp->right==NULL){
        (*root)=NULL;
        return;
      }
      (*root)=tmp->right;
      // cout<<"root= "<<(*root)->str<<endl;
      (*root)->parent=NULL;
      free(tmp);
      return;
    }
    if(tmp==tmp->parent->left){
      tmp->parent->left=tmp->right;
      if(tmp->right!=NULL){
        tmp->right->parent=tmp->parent;
      }
      // free(tmp);
      return ;
    }
    else{
      tmp->parent->right=tmp->right;
      if(tmp->right!=NULL){
        tmp->right->parent=tmp->parent;
      }
      // free(tmp);
      return ;
    }
  }
  if(tmp->right==NULL){
    // cout<<"right==NULL"<<endl;
    if(tmp->parent==NULL){
      // cout<<"parent==NULL"<<endl;
      // cout<<"root= "<<(*root)->str<<endl;
      (*root)=tmp->left;
      (*root)->parent=NULL;
      // cout<<"root= "<<(*root)->str<<endl;
      return;
    }
    if(tmp==tmp->parent->left){
      tmp->parent->left=tmp->left;
      if(tmp->left!=NULL){
        tmp->left->parent=tmp->parent;
      }
      // free(tmp);
      return ;
    }
    else{
      tmp->parent->right=tmp->left;
      if(tmp->left!=NULL){
        tmp->left->parent=tmp->parent;
      }
      // free(tmp);
      return ;
    }
  }
  Node*suc=succ(tmp);
  string s=suc->str;
  del(root,suc,1); //bad algorithm
  tmp->str=s;
  return ;
}

void inorder(Node* root,int flag){ //flag 0 means initialize rank to zero only when inorder() is called in main function
  static int rank=0;
  if(flag==0) rank=0;
  if(root==NULL) return;
  inorder(root->left,1);
  rank++;
  root->rank=rank;
  // cout<<root->str<<"  : "<<root->rank<<endl;
  inorder(root->right,1);
  return;
}


int main(){
  Node*root=NULL;
  int t,i;
  string cmd,str;
  cin>>t;
  for(i=0;i<t;i++){
    cin>>cmd>>str;
    if(cmd=="learn"){
      root=insertNode(root,str);
    }
    else if(cmd=="forget"){
      inorder(root,0);
      // cout<<"root before deleting: "<<root->str<<endl;
      del(&root,find(root,str),0);
      // cout<<"root after deleting:  "<<root->str<<endl;
    }
    else if(cmd=="findrank"){
      inorder(root,0);
      cout<<find(root,str)->rank<<endl;
    }
    // else if(cmd=="parent"){
    //   cout<<root->parent->str<<endl;
    // }
  }
  // cout<<find(root,"amit")->str;
  // cout<<(root->right->right==NULL)<<endl;
  // del(root,find(root,"zb"));
  // cout<<succ(root)->str<<endl;
  // inorder(root,0);
  // while(root!=NULL){
  //   cout<<root->str;
  //   if(root->parent==NULL){
  //     cout<< "  : no parent"<<"   : "<<root->rank<<endl;
  //   }
  //   else{
  //     cout<<"   : "<<root->parent->str<<"   : "<<root->rank<<endl;
  //   }
  //   root=root->right;
  // }


}
