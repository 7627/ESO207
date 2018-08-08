#include<iostream>
using namespace std;

struct node{
  string str;
  int l_count;
  struct node* parent;
  struct node*left;
  struct node*right;
};
typedef struct node Node;

Node* createNode(string str){
  Node* tmp=(Node*)calloc(1,sizeof(Node));
  tmp->str=str;
  tmp->l_count=1;
  return tmp;
}

Node* insertNode(Node*root,string str){
  Node*tmp=root;
  int count=1;
  if(root==NULL){
    root=createNode(str);
    // root->l_count=1;
    return root;
  }
  while(root!=NULL){
    if(str==root->str){
      // cout<<"already present";
      return tmp;
    }
    if(str<root->str){
      root->l_count+=1;
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



string succ(Node* root){
  root=root->right;
  // cout<<"yoyoo"<<endl;
  while(root->left!=NULL){
    // cout<<root->str<<endl;
    root=root->left;
  }
  return root->str;
}

int findrank(Node*root,string str){
  int rank=0;
  while(root->str!=str){
    if(str>root->str){
      rank=rank+root->l_count;
      root=root->right;
    }
    else{
      root=root->left;
    }
  }
  return rank+root->l_count;
}


void del(Node** root, string delete_it,int flag){
  Node*tmp=(*root);
  if(flag==0){
    cout<<findrank(tmp,delete_it)<<endl;
  }
  while(tmp->str!=delete_it){
    if(delete_it<tmp->str){
      // cout<<tmp->str<<" earlier l_count: "<<tmp->l_count;
      tmp->l_count-=1;
      // cout<<" later : "<<tmp->l_count<<endl;
      tmp=tmp->left;
    }
    else{
      tmp=tmp->right;
    }
  }



  // cout<<"delete_it : "<<tmp->str<<endl;

  if(tmp->left==NULL){
    // cout<<"left==NULL"<<endl;
    if(tmp->parent==NULL){
      // cout<<"parent==NULL"<<endl;
      // cout<<"root= "<<(*root)->str<<endl;
      (*root)=tmp->right;
      if(*root!=NULL){ //handles case when graph has only one node and it is being deleted
        // cout<<"root= "<<(*root)->str<<endl;
        (*root)->parent=NULL;///////////////////
      }
      free(tmp);
      return;
    }
    if(tmp==tmp->parent->left){
      tmp->parent->left=tmp->right;
      if(tmp->right!=NULL){
        tmp->right->parent=tmp->parent;
      }
      free(tmp);
      return ;
    }
    else{
      tmp->parent->right=tmp->right;
      if(tmp->right!=NULL){
        tmp->right->parent=tmp->parent;
      }
      free(tmp);
      return ;
    }
  }
  if(tmp->right==NULL){
    // cout<<"right==NULL"<<endl;
    if(tmp->parent==NULL){
      // cout<<"parent==NULL"<<endl;
      // cout<<"root= "<<(*root)->str<<endl;
      (*root)=tmp->left;
      if(*root!=NULL){
        (*root)->parent=NULL;
        // cout<<"root= "<<(*root)->str<<endl;
      }
      free(tmp);
      return;
    }
    if(tmp==tmp->parent->left){
      tmp->parent->left=tmp->left;
      if(tmp->left!=NULL){
        tmp->left->parent=tmp->parent;
      }
      free(tmp);
      return ;
    }
    else{
      tmp->parent->right=tmp->left;
      if(tmp->left!=NULL){
        tmp->left->parent=tmp->parent;
      }
      free(tmp);
      return ;
    }
  }

  string s=succ(tmp);
  del(&tmp,s,1); //good algorithm
  tmp->str=s;
  return ;
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
      // cout<<"root before deleting: "<<root->str<<endl;
      del(&root,str,0);
      // cout<<"root after deleting:  "<<root->str<<endl;
    }
    else if(cmd=="findrank"){
      cout<<findrank(root,str)<<endl;
    }
  }
  // while(root!=NULL){
  //   cout<<root->str<<" : "<<root->l_count<<endl;
  //   root=root->left;
  // }

}
