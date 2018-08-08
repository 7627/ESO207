//Make a BST class

#include<iostream>
using namespace std;

typedef struct node{
  string w;
  int l_count;
  struct node* left;
  struct node* right;
  struct node* parent;
} Node;

class BST{
private:
  Node* root;

public:
  BST(){
    root = NULL;
  }
private:
  Node* createNode(string word){
    Node* tmp = (Node*)calloc(1,sizeof(Node));
    tmp->w = word;
    tmp->l_count = 1;
    return tmp;

  }

  Node* findword(string word){
    Node* tmp = root;
    while(tmp->w != word && tmp != NULL){
      if(word < tmp->w){
        tmp = tmp->left;
      }
      else{
        tmp = tmp->right;
      }
    }
    if(tmp == NULL){
      cout<<"ERROR: "<<word<<" not found "<<endl;
    }
    return tmp;
  }

  Node* findSuccessor(Node* tmp_root, string word){
    Node* tmp = tmp_root->right;
    while(tmp->left != NULL){
      tmp = tmp->left;
    }
    return tmp;
  }

public:
  void learn(string word){
    if(root == NULL){
      root = createNode(word);
      return;
    }
    Node* tmp = root;
    while(tmp != NULL){
      if(word > tmp->w){
        if(tmp->right == NULL){
          tmp->right = createNode(word);
          tmp->right->parent = tmp;
          break;
        }
        tmp = tmp->right;
      }
      else{
        tmp->l_count++;
        if(tmp->left == NULL){
          tmp->left = createNode(word);
          tmp->left->parent = tmp;
          break;
        }
        tmp = tmp->left;
      }
    }
    return;
  }

  int findrank(string word){
    Node* tmp = root;
    int rank = 0;
    while(tmp->w != word && tmp != NULL){
      if(word < tmp->w){
        tmp = tmp->left;
      }
      else if(word > tmp->w){
        rank = rank + tmp->l_count;
        tmp = tmp->right;
      }
    }
    if(tmp == NULL){
      cout<<word<<" not in the tree"<<endl;
      return -1;
    }
    else{
      rank = rank + tmp->l_count;
    }
    return rank;

  }

  void forget(string word){
    Node* tmp = findword(word);
    if(tmp->left == NULL){
      if(tmp == root){
        root = tmp->right;
        return;
      }
      if(tmp == tmp->parent->right){
        tmp->parent->right = tmp->right;
      }
      else{
        tmp->parent->left = tmp->right;
      }
      if(tmp->right != NULL){
        tmp->right->parent = tmp->parent;
      }
      free(tmp);
    }
    else if(tmp->right == NULL){
      if(tmp == root){
        root = tmp->left;
        return;
      }
      if(tmp == tmp->parent->right){
        tmp->parent->right = tmp->left;
      }
      else{
        tmp->parent->left = tmp->left;
      }
      if(tmp->left != NULL){
        tmp->left->parent = tmp->parent;
      }
      free(tmp);
    }
    else{
      Node* succ = findSuccessor(tmp,word);
      tmp->w = succ->w;
      if(succ == succ->parent->left){
        succ->parent->left = succ->right;
      }
      else{
        succ->parent->right = succ->right;
      }
      if(succ->right != NULL){
        succ->right->parent = succ->parent;
      }
    }
  }

  void print(){
    // prints the structure of tree
    Node* tmp = root;
    cout<<"left branch"<<endl;
    while(tmp != NULL){
      cout<<tmp->w<<" l_count= "<<tmp->l_count<<endl;
      tmp = tmp->left;
    }
    cout<<endl;
    tmp = root;
    cout<<"right branch"<<endl;
    while(tmp != NULL){
      cout<<tmp->w<<" l_count= "<<tmp->l_count<<endl;
      tmp = tmp->right;
    }
  }


};

int main(){
  BST root;
  int n,i;
  string cmd, word;
  cin>>n;
  for(i=0;i<n;i++){
    cin>>cmd>>word;
    if(cmd == "l"){
      root.learn(word);
    }
    else if(cmd == "fi"){
      cout<<"Rank of "<<word<<" is "<<root.findrank(word)<<endl;
    }
    else if(cmd == "fo"){
      cout<<"forgetting "<<word<<" rank= "<<root.findrank(word)<<endl;
      root.forget(word);
    }
    else{
      cout<<"Invalid command"<<endl;
      i--;
    }
    root.print();
    cout<<endl<<endl;
  }
}
