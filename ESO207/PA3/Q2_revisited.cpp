// 28th June 2018
// Practicing cpp-codes
// completed successfully on the same day
#include<iostream>
using namespace std;

typedef struct Node{
  string w; //word
  int l_count;
  struct Node* left;
  struct  Node* right;
  struct Node* parent;
}Node;

Node* createNode(string word){
  Node* temp;
  temp = (Node*)calloc(1,sizeof(Node));
  temp->w = word;
  temp->l_count = 1;
  return temp;
}

Node* learn(Node* root, string word){
  Node* temp=root;
  if(root==NULL){
    root = createNode(word);
    return root;
  }

  while(root!=NULL){
    if(word < root->w){
      if(root->left != NULL){
        root->l_count++;
        root = root->left;
      }
      else{
        root->left = createNode(word);
        root->left->parent=root;
        root->l_count++;
        return temp;
      }
    }
    else if(word > root->w){
      if(root->right != NULL)
        root = root->right;
      else{
        root->right = createNode(word);
        root->right->parent=root;
        return temp;
      }
    }
    else{
      cout<<word<<" is already learnt"<<endl;
      return temp;
    }
  }
}

int findrank(Node* root, string word){
  int rank=0;
  while(root->w != word){
    if(word < root->w){
      root = root->left;
    }
    else{
      rank += root->l_count;
      root = root->right;
    }
  }
  rank += root->l_count;
  return rank;
}

Node* findword(Node*root, string word){
  while(root->w != word){
    if(word < root->w){
      root->l_count--;
      root = root->left;
    }
    else
      root = root->right;
  }
  return root;
}

Node* successor(Node*w){
  w=w->right;
  while(w->left!=NULL){
    w->l_count--;
    w=w->left;
  }
  return w;
}

Node* forget(Node* root, string word){
  Node* tmp=findword(root,word);
  // int rank = findrank(root,word);

  if(tmp->left == NULL){
    if(tmp==root){
      Node* x=tmp->right;
      free(tmp);
      return x;
    }
    if(tmp == tmp->parent->left){
      tmp->parent->left = tmp->right;
      }
    else{
      tmp->parent->right = tmp->right;
    }
    if(tmp->right!=NULL){
      tmp->right->parent = tmp->parent;
    }
    free(tmp);
    return root;
  }

  else if(tmp->right == NULL){
    if(tmp==root){
      Node* x=tmp->left;
      free(tmp);
      return x;
    }
    if(tmp == tmp->parent->left){
      tmp->parent->left = tmp->left;
    }
    else{
      tmp->parent->right = tmp->left;
    }
    if(tmp->left!=NULL){
      tmp->left->parent = tmp->parent;
    }
    free(tmp);
    return root;
  }

  else{
    Node* succ = successor(tmp);
    string t = succ->w;
    forget(tmp,succ->w);
    tmp->w = t;
    return root;
  }



}

int main(){
  Node* root = NULL;
  int n,i;
  string cmd,word;
  cin >> n;
  for(i=0;i<n;i++){
    cin >>cmd>>word;
    if(cmd=="l"){
      root = learn(root,word);
    }
    if(cmd=="fi"){
      cout<<findrank(root,word)<<endl;
    }
    if(cmd=="fo"){
      cout<<findrank(root,word)<<endl;
      root=forget(root,word);
      // cout<<"forgetting "<<word<<" rank= "<<forget(root,word)<<endl;
    }

    Node*tmp=root;
    while(tmp!=NULL){
      cout<<tmp->w<<" l_count= "<<tmp->l_count<<" rank= "<<findrank(root,tmp->w)<<endl;
      tmp=tmp->left;
    }
    tmp=root;
    while(tmp!=NULL){
      cout<<tmp->w<<" l_count= "<<tmp->l_count<<" rank= "<<findrank(root,tmp->w)<<endl;
      tmp=tmp->right;
    }
  }
}
