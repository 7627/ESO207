#include<iostream>
using namespace std;

struct node{
  string str;
  int l_count;
  int height, BF; //BF = height(right - left)
  struct node* parent;
  struct node*left;
  struct node*right;
};
typedef struct node Node;

int max(int a, int b){
  return a>=b? a:b;
}

int height(Node* x){
  int lh,rh;
  if(x==NULL) return -1;
  if(x->left==NULL){
    lh=-1;
  }
  else{
    lh=x->left->height;
  }
  if(x->right==NULL){
    rh=-1;
  }
  else{
    rh=x->right->height;
  }
  x->BF=rh-lh;
  // cout<<"BF of "<<x->str<<" is "<<x->BF<<" lh rh = "<<lh<<rh<<endl;
  return max(lh,rh)+1;
}

Node* L_rot(Node* x){
  Node* y=x->right;
  x->right=y->left;
  if(y->left!=NULL) y->left->parent=x;
  y->left=x;
  y->parent=x->parent;
  x->parent=y;
  x->height=height(x);
  y->height=height(y);
  y->l_count=y->l_count + x->l_count;
  // cout<<"after L_rot on  "<<x->str<<" height: "<<x->height<<" BF= "<<x->BF<<" l_count= "<<x->l_count<<endl;
  // cout<<"after L_rot, root is  "<<y->str<<" height: "<<y->height<<" BF= "<<y->BF<<" l_count= "<<y->l_count<<endl;
  return y;
}

Node* R_rot(Node* x){
  Node* y=x->left;
  x->left=y->right;
  if(y->right!=NULL) y->right->parent=x;
  y->right=x;
  y->parent=x->parent;
  x->parent=y;
  x->height=height(x);
  y->height=height(y);
  x->l_count=x->l_count - y->l_count;
  // cout<<"after R_rot on  "<<x->str<<" height: "<<x->height<<" BF= "<<x->BF<<" l_count= "<<x->l_count<<endl;
  // cout<<"after R_rot, root is  "<<y->str<<" height: "<<y->height<<" BF= "<<y->BF<<" l_count= "<<y->l_count<<endl;
  return y;
}


Node* createNode(string str){
  Node* tmp=(Node*)calloc(1,sizeof(Node));
  tmp->str=str;
  tmp->l_count=1;
  tmp->height=0;
  tmp->BF=0;
  return tmp;
}



Node* insertNode(Node* root, string str){
  Node* tmp=root;

  if(root==NULL){
    tmp=createNode(str);
    return tmp;
  }
  while(root!=NULL){
    if(root->str==str){
      return tmp;
    }
    if(str < root->str){
      root->l_count++;
      if(root->left==NULL){
        root->left=createNode(str);
        root->left->parent=root;
        // root=root->left;
        break;
        // return tmp;
      }
      else{
        root=root->left;
      }
    }

    else{
      if(root->right==NULL){
        root->right=createNode(str);
        root->right->parent=root;
        // root=root->right;
        // return tmp;
        break;
      }
      else{
        root=root->right;
      }
    }
  }

  while(root!=NULL){ //right now root is pointing to the last added
    // int h_l, h_r;
    // cout<<"checking root="<<root->str<<" height= "<<root->height<<endl;
    root->height=height(root);
    // cout<<"BF of "<<root->str<<" is "<<root->BF<<endl;
    // h_r=(root->right==NULL)? -1:root->right->height;
    // h_l=(root->left==NULL)? -1:root->left->height;


    if(abs(root->BF) <= 1){
      root=root->parent;
      continue;
    }
    // cout<<"dikkat ho gyi"<<endl;
    //4 case possible now: LL (left of left is heavier), RR, LR(), RL(left of right is heavier e.g 2,4,3)
    if(root->BF>0){ //2 case possible: RR, RL;

      if(root->right->BF>0){ //i.e 2,3,4 when 2 is root
        // cout<<"RR case at node= "<<root->str<<endl;
        if(root->parent==NULL){
          tmp=L_rot(root);
          break;
        }
        if(root==root->parent->left)
         root->parent->left=L_rot(root); //instead of root I should write root->parent->left/right;
        else
          root->parent->right=L_rot(root);
        root=root->parent->parent;
        continue;
      }

      else{
        // cout<<"RL case at node= "<<root->str<<endl;
        root->right=R_rot(root->right);
        if(root->parent==NULL){
          tmp=L_rot(root);
          break;
        }
        if(root==root->parent->left){
          root->parent->left=L_rot(root);
        }
        else{
          root->parent->right=L_rot(root);
        }
        root=root->parent->parent;
        continue;
      }
    }

    else{

      if(root->left->BF<0){
        // cout<<"LL case at node= "<<root->str<<endl;
        if(root->parent==NULL){
          tmp=R_rot(root);
          break;
        }
        if(root==root->parent->left)
         root->parent->left=R_rot(root); //instead of root I should write root->parent->left/right;
        else
          root->parent->right=R_rot(root);
        root=root->parent->parent;
        continue;
      }


      else{
        // cout<<"LR case at node= "<<root->str<<endl;
        root->left=L_rot(root->left);
        if(root->parent==NULL){
          tmp=R_rot(root);
          break;
        }
        if(root==root->parent->left){
          root->parent->left=R_rot(root);
        }
        else{
          root->parent->right=R_rot(root);
        }
        root=root->parent->parent;
        continue;
      }
    } //bigger else block ends here


  } //bigger while loop ends here


  return tmp;
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


string succ(Node* root){
  root=root->right;
  // cout<<"yoyoo"<<endl;
  while(root->left!=NULL){
    // cout<<root->str<<endl;
    root=root->left;
  }
  return root->str;
}



void del(Node** root, string delete_it,int flag){
  Node*tmp=(*root);
  Node* x;
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
      if(*root!=NULL){ //handles case when graph's root node is being deleted
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
      for( x=tmp->parent;x!=NULL;x=x->parent){
        // cout<<"in delete: "<<x->str<<endl;
        x->height=height(x);
      }
      free(tmp);
      return ;
    }
    else{
      tmp->parent->right=tmp->right;
      if(tmp->right!=NULL){
        tmp->right->parent=tmp->parent;
      }
      for(x=tmp->parent;x!=NULL;x=x->parent){
        // cout<<"in delete: "<<x->str<<endl;
        x->height=height(x);
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
      for( x=tmp->parent;x!=NULL;x=x->parent){
        // cout<<"in delete: "<<x->str<<endl;
        x->height=height(x);
      }
      free(tmp);
      return ;
    }
    else{
      tmp->parent->right=tmp->left;
      if(tmp->left!=NULL){
        tmp->left->parent=tmp->parent;
      }
      for(x=tmp->parent;x!=NULL;x=x->parent){
        // cout<<"in delete: "<<x->str<<endl;
        x->height=height(x);
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


void preorder(Node* root,int flag){ //flag 0 means initialize rank to zero only when inorder() is called in main function
  static int rank=0;
  if(flag==0) rank=0;
  if(root==NULL) return;
  rank++;
  cout<<"node: "<<root->str;
  if(root->left!=NULL)
  cout<<" ->left "<<root->left->str;
  if(root->right!=NULL)
  cout<<" ->right "<<root->right->str;
  if(root->parent!=NULL)
  cout<<" parent: "<<root->parent->str;
  cout<<" height: "<<root->height<<" BF: "<<root->BF<<" l_count: "<<root->l_count<<endl;
  // cout<<root->str<<"  : "<<root->rank<<endl;
  preorder(root->left,1);
  preorder(root->right,1);
  return;
}

void postorder(Node* root){ //flag 0 means initialize rank to zero only when inorder() is called in main function
  if(root==NULL) return;
  postorder(root->left);
  // cout<<"rank of "<<root->str<<" is: "<<rank<<endl;
  // cout<<root->str<<"  : "<<root->rank<<endl;
  postorder(root->right);
  free(root);
  return;
}

int main(){
  int i,t;
  Node* root=NULL;
  string str,cmd;
  cin>>t;
  for(i=0;i<t;i++){
    cin>>cmd>>str;
    if(cmd=="learn"){
      root=insertNode(root,str);
      // cout<<"inserted "<<str<<" and root is "<<root->str<<endl;
    }
    else if(cmd=="forget"){
      del(&root,str,0);
    }
    else if(cmd=="findrank"){
      cout<<findrank(root,str)<<endl;
    }
    // else if(cmd=="in") inorder(root,0);
    // preorder(root,0);
    // for(Node* x=root; x!=NULL; x=x->left){
    //   cout<<"left traversal: "<<x->str<<" height: "<<x->height<<" BF= "<<x->BF<<" l_count= "<<x->l_count<<endl;
    // }
    // for(Node* x=root; x!=NULL; x=x->right){
    //   cout<<"right traversal: "<<x->str<<" height: "<<x->height<<" BF= "<<x->BF<<" l_count= "<<x->l_count<<endl;
    // }
    // cout<<root->str<<endl;
    // cout<<"insrting "<<str<<endl;
  }
  postorder(root);
  return 0;
}
