#include<iostream>
using namespace std;

typedef struct Node{
  string w; //word
  int l_count;
  struct Node* left;
  struct  Node* right;
  struct Node* parent;
}Node;

class BST{
private:
  Node* root = NULL;
  int yo=1;

  Node* createNode(string word){
    Node* temp;
    temp = (Node*)calloc(1,sizeof(Node));
    temp->w = word;
    temp->l_count = 1;
    return temp;
  }

public:
  void learn(string word){
    Node* temp=root;
    if(root==NULL){
      root = createNode(word);
      return;
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
          root = temp;
          return ;
        }
      }
      else if(word > root->w){
        if(root->right != NULL)
          root = root->right;
        else{
          root->right = createNode(word);
          root->right->parent=root;
          root = temp;
          return ;
        }
      }
      else{
        cout<<word<<" is already learnt"<<endl;
        root = temp;
        return ;
      }
    }
  }

  int findrank(string word){
    int rank=0;
    Node* tmp = root;
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
    root = tmp;
    return rank;
  }

private:
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

public:
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


};

int main(){
  BST tree;
  int n,i;
  string cmd,word;
  cin >> n;
  for(i=0;i<n;i++){
    cin >>cmd>>word;
    if(cmd=="l"){
      tree.learn(word);
    }
    // if(cmd=="fi"){
    //   cout<<findrank(root,word)<<endl;
    // }
    // if(cmd=="fo"){
    //   cout<<findrank(root,word)<<endl;
    //   root=forget(root,word);
      // cout<<"forgetting "<<word<<" rank= "<<forget(root,word)<<endl;
    // }

    Node*tmp=tree.root;
    while(tmp!=NULL){
      cout<<tmp->w<<" l_count= "<<tmp->l_count<<" rank= "<<tree.findrank(tmp->w)<<endl;
      tmp=tmp->left;
    }
    tmp=tree.root;
    while(tmp!=NULL){
      cout<<tmp->w<<" l_count= "<<tmp->l_count<<" rank= "<<tree.findrank(tmp->w)<<endl;
      tmp=tmp->right;
    }
  }
}
