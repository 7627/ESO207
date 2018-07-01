#include<iostream>
#include<vector>
using namespace std;

int max_count=0;
struct node{
  string str;
  int l_count;
  int count;
  int height, BF; //BF = height(right - left)
  struct node* parent;
  struct node*left;
  struct node*right;
};
typedef struct node Node;

Node* max_ptr;

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
Node* createNode(string str){
  Node* tmp=(Node*)calloc(1,sizeof(Node));
  tmp->str=str;
  tmp->l_count=1;
  tmp->height=0;
  tmp->BF=0;
  tmp->count=1;
  if(tmp->count>max_count){
    max_count=tmp->count;
    max_ptr=tmp;
  }
  return tmp;
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

Node* insertNode(Node* root, string str){
  Node* tmp=root;

  if(root==NULL){
    tmp=createNode(str);
    return tmp;
  }
  while(root!=NULL){
    if(root->str==str){
      root->count+=1;
      if(root->count>max_count){
        max_count=root->count;
        max_ptr=root;
      }
      // cout<<root->str<<" "<<root->count<<endl;
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


int main(){
  int i,n,t,flag;
  int max=0, max_index=0;
  Node* root=NULL;
  string str;
  cin>>n;
  for(t=0;t<n;t++){
    cin>>str;
    root=insertNode(root,str);
  }
  cout<<max_ptr->str<<endl;
  return 0;
}
