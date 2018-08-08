#include<iostream>
using namespace std;

struct node{
  string str;
  int l_count;
  int l_height, r_height; // BF= height(right) - height(left)
  int height;
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
  x->l_height=lh;
  x->r_height=rh;
  return max(lh,rh)+1;
}


Node* L_rot(Node* x){
  Node* y=x->right;
  x->right=y->left;
  y->left=x;
  y->parent=x->parent;
  x->parent=y;
  x->r_height=y->l_height;
  x->height=max(x->l_height, x->r_height)+1;
  y->l_height=x->height;
  y->height=max(y->l_height, x->r_height)+1;
  y->l_count=y->l_count + x->l_count;
  // cout<<"after L_rot on  "<<x->str<<" height: "<<x->height<<" l_height: "<<x->l_height<<" r_height: "<<x->r_height<<" l_count= "<<x->l_count<<endl;
  // cout<<"after L_rot, root is  "<<y->str<<" height: "<<y->height<<" l_height: "<<y->l_height<<" r_height: "<<y->r_height<<" l_count= "<<y->l_count<<endl;
  return y;
}

Node* R_rot(Node* x){
  Node* y=x->left;
  x->left=y->right;
  y->right=x;
  y->parent=x->parent;
  x->parent=y;
  x->l_height=y->r_height;
  x->height=max(x->l_height, x->r_height)+1;
  y->r_height=x->height;
  y->height=max(y->l_height, y->r_height)+1;
  x->l_count=x->l_count - y->l_count;
  // cout<<"after R_rot on  "<<x->str<<" height: "<<x->height<<" l_height: "<<x->l_height<<" r_height: "<<x->r_height<<" l_count= "<<x->l_count<<endl;
  // cout<<"after R_rot, root is  "<<y->str<<" height: "<<y->height<<" l_height: "<<y->l_height<<" r_height: "<<y->r_height<<" l_count= "<<y->l_count<<endl;
  return y;
}

Node* createNode(string str){
  Node* tmp=(Node*)calloc(1,sizeof(Node));
  tmp->str=str;
  tmp->l_count=1;
  tmp->height=0;
  tmp->l_height=-1; //height of left subtree
  tmp->r_height=-1; //height of right subtree
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
        root=root->left;
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
        root=root->right;
        // return tmp;
        break;
      }
      else{
        root=root->right;
      }
    }
  }
  while(root->parent!=NULL){ //right now root is pointing to the last added
    int h_l, h_r;
    // cout<<"checking root="<<root->str<<" height= "<<root->height<<endl;
    if(root==root->parent->left){
      // cout<<root->str<<" is left child of "<<root->parent->str<<endl;
      h_l=root->height;
      root->parent->l_height=root->height;
      if(root->parent->right==NULL){
        h_r=-1;
        root->parent->r_height=-1;
      }
      else{
        h_r=root->parent->right->height;
        root->parent->r_height=root->parent->right->height;
      }
    }

    else{
      // cout<<root->str<<" is right child of "<<root->parent->str<<endl;
      h_r=root->height;
      root->parent->r_height=root->height;
      if(root->parent->left==NULL){
        h_l=-1;
        root->parent->l_height=-1;
      }
      else{
        h_l=root->parent->left->height;
        root->parent->l_height=root->parent->left->height;
      }
    }

    if(abs(h_r - h_l) <= 1){
      root=root->parent;
      root->height=max(h_l,h_r)+1;
      continue;
    }
    // cout<<"dikkat ho gyi"<<endl;
    root=root->parent;
    //4 case possible now: LL (left of left is heavier), RR, LR(), RL(left of right is heavier e.g 2,4,3)
    if(h_r > h_l){ //2 case possible: RR, RL;

      if(root->right->r_height > root->right->l_height){ //i.e 2,3,4 when 2 is root
        // cout<<"RR case at node= "<<root->str<<endl;
        if(root->parent==NULL){
          tmp=L_rot(root);
          break;
        }
        if(root==root->parent->left)
         root->parent->left=L_rot(root); //instead of root I should write root->parent->left/right;
        else
          root->parent->right=L_rot(root);
        root=root->parent;
      }

      else{
        // cout<<"RL case at node= "<<root->str<<endl;
        root->right=R_rot(root->right);
        if(root->parent==NULL){
          tmp=L_rot(root);
          break;
        }
        if(root=root->parent->left){
          root->parent->left=L_rot(root);
        }
        else{
          root->parent->right=L_rot(root);
        }
        root=root->parent;
      }
    }

    else{

      if(root->left->l_height > root->left->r_height){
        // cout<<"LL case at node= "<<root->str<<endl;
        if(root->parent==NULL){
          tmp=R_rot(root);
          break;
        }
        if(root==root->parent->left)
         root->parent->left=R_rot(root); //instead of root I should write root->parent->left/right;
        else
          root->parent->right=R_rot(root);
        root=root->parent;
      }


      else{
        // cout<<"LR case at node= "<<root->str<<endl;
        root->left=L_rot(root->left);
        if(root->parent==NULL){
          tmp=R_rot(root);
          break;
        }
        if(root=root->parent->left){
          root->parent->left=R_rot(root);
        }
        else{
          root->parent->right=R_rot(root);
        }
        root=root->parent;
      }
    } //bigger else block ends here


  } //bigger while loop ends here






    // }


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





















int main(){
  int i,t;
  Node* root=NULL;
  string str,cmd;
  cin>>t;
  for(i=0;i<t;i++){
    cin>>cmd>>str;
    if(cmd=="l"){
      root=insertNode(root,str);
      // cout<<"inserted "<<str<<" and root is "<<root->str<<endl;
    }
    else if(cmd=="fo"){
      del(&root,str,0);
    }
    else if(cmd=="fi"){
      cout<<findrank(root,str)<<endl;
    }
    for(Node* x=root; x!=NULL; x=x->left){
      cout<<"left traversal: "<<x->str<<" height: "<<x->height<<" l_height: "<<x->l_height<<" r_height: "<<x->r_height<<" l_count= "<<x->l_count<<endl;
    }
    for(Node* x=root; x!=NULL; x=x->right){
      cout<<"right traversal: "<<x->str<<" height: "<<x->height<<" l_height: "<<x->l_height<<" r_height: "<<x->r_height<<" l_count= "<<x->l_count<<endl;
    }
    // cout<<root->str<<endl;
    // cout<<"insrting "<<str<<endl;
  }
  return 0;
}
