// All 4 airthmatics, very inefficient divide

#include<stdio.h>
#include<stdlib.h>
struct node{
  int digit;
  struct node* next;
};
struct node* insert_at_front(struct node* head,int x){
   struct node* temp;
   temp=calloc(1,sizeof(struct node));
   temp->digit=x;
   temp->next=head;
   // head=temp;
   return temp;
 }
struct node* scan_number(int size){
   int i=0;
   struct node* temp=NULL;
   for(i=0;i<size;i++){
    temp=insert_at_front(temp,getchar()-'0');
   }
   return temp;
 }
void print_list(struct node* head){
  struct node* temp=head;
  if(temp==NULL){
    return;
  }
  print_list(temp->next);
  printf("%d",temp->digit);
  // while(temp!=NULL){
  //   printf("%d",temp->digit);
  //   temp=temp->next;
  // }
  // printf("\n");
}

// int lessThan(struct node*number1,struct node* number2){
//   if(number2==NULL){
//     return 0;
//   }
//   if(number1==NULL){
//     return 1;
//   }
// }

struct node* add(struct node* number1,struct node* number2){
  struct node* result, *head=NULL;
  int carry=0,i=0;
  while(number1!=NULL & number2!=NULL){
    if(i==0){
      result=calloc(1,sizeof(struct node));
      head=result;
      i=1;
    }
    else{
      result->next=calloc(1,sizeof(struct node));
      result=result->next;
    }
    result->digit=(number1->digit + number2->digit + carry)%10;
    carry=(number1->digit + number2->digit + carry)/10;
    number1=number1->next;
    number2=number2->next;
    // printf("%d",result->digit);
  }
  while(number1!=NULL){
    result->next=calloc(1,sizeof(struct node));
    result=result->next;
    result->digit=(number1->digit + carry)%10;
    carry=(number1->digit + carry)/10;
    number1=number1->next;
  }
  while(number2!=NULL){
    result->next=calloc(1,sizeof(struct node));
    result=result->next;
    result->digit=(number2->digit + carry)%10;
    carry=(number2->digit + carry)/10;
    number2=number2->next;
  }
  if(carry==1){
    result->next=calloc(1,sizeof(struct node));
    result=result->next;
    result->digit=1;
  }
  return head;
}

struct node* multiply(struct node*number1, struct node* number2,int n1, int n2){
  struct node* result;
  struct node* final_result=calloc(1,sizeof(struct node));
  final_result->digit=0;// initiated the final result equal to zero.
  int i=0,carry=0,j=0,iteration=0;
  struct node*temp;
  struct node* no1=number1, *no2=number2;
  while(no2!=NULL){
    while(no1!=NULL){
      if(j==0){
        result=calloc(1,sizeof(struct node));
        temp=result;
        j=1;
      }
      else{
        result->next=calloc(1,sizeof(struct node));
        result=result->next;
      }
      result->digit=(no2->digit*no1->digit + carry)%10;
      carry=(no2->digit*no1->digit + carry)/10;
      no1=no1->next;
    }
    if(carry!=0){
      result->next=calloc(1,sizeof(struct node));
      result=result->next;
      result->digit=carry;
      carry=0;
    }
    no1=number1;//reinitialised variables
    j=0; result=NULL;
    for(i=0;i<iteration;i++){//multiplies the multiplication by multiples of 10
      temp=insert_at_front(temp,0);
    }
    iteration++;
    final_result=add(final_result,temp);
    no2=no2->next;
  }
  return final_result;
}

struct node* subtract(struct node* number1, struct node* number2){
  struct node* result,*temp;
  int i=0,carry=0;
  while(number1!=NULL & number2!=NULL){
    if(i==0){
      result=calloc(1,sizeof(struct node));
      i=1;
      temp=result;
    }
    else{
      result->next=calloc(1,sizeof(struct node));
      result=result->next;
    }
    if(number1->digit - carry >= number2->digit){
      result->digit=(number1->digit - number2->digit - carry);
      carry=0;
    }
    else{
      result->digit=(number1->digit - number2->digit - carry + 10);
      carry=1;
    }
    number1=number1->next;
    number2=number2->next;
  }
  while(number1!=NULL){
    result->next=calloc(1,sizeof(struct node));
    result=result->next;
    if(number1->digit - carry >= 0 ){
      result->digit=(number1->digit - carry);
      carry=0;
    }
    else{
      result->digit=(number1->digit - carry + 10);
      carry=1;
    }
    number1=number1->next;
  }
  if(number2!=NULL){
    struct node* temp1=calloc(1,sizeof(struct node));
    temp1->digit=-1;
    // printf("Not valid\n");
    return temp1;
  }
  if(result->digit==-1 || ((number1==NULL && number2==NULL) && carry==1)){
    struct node* temp1=calloc(1,sizeof(struct node));
    temp1->digit=-1;
    // printf("Not valid\n");
    return temp1;
  }
  return temp;
}

struct node* divide(struct node* number1,struct node* number2){
  struct node* result, *temp=number1;
  result=calloc(1,sizeof(struct node));
  result->digit=-1;//initialised result to zero;
  struct node* add_one=calloc(1,sizeof(struct node));
  add_one->digit=1;//add_one is used to add one to any number;
  while(temp->digit!=-1){
    temp=subtract(temp,number2);
    result=add(result,add_one);
    // print_list(temp);printf("\n");
  }
  return result;
}

int main(){
  int t,i=0;
  scanf("%d",&t);
  for(i=0;i<t;i++){
     int n1,n2,x;
     scanf("%d %d",&n1,&n2); //n1 and n2 are the number of digits in number1 and number2 resp.
     struct node* number1,*number2;
     // int i=0;
     getchar();
     number1=scan_number(n1);
     getchar();
     number2=scan_number(n2);
     int opcode;
     scanf("%d",&opcode);
     struct node* addition=NULL, *multiplication=NULL, *subtraction=NULL, *division=NULL;
     // print_list(number1);printf("\n");
     // print_list(number2);printf("\n");
     switch(opcode){
       case 1:
         addition=add(number1,number2);
         /*printf("Addition of numbers= ");*/print_list(addition);printf("\n");
         break;
       case 3:
         multiplication=multiply(number1,number2,n1,n2);
         /*printf("Multiplication of numbers= ");*/print_list(multiplication);printf("\n");
         break;
       case 2:
         subtraction=subtract(number1,number2);
         /*printf("Subtraction of numbers= ");*/print_list(subtraction);printf("\n");
         break;
       case 4:
         division=divide(number1,number2);
         /*printf("Division of numbers= ");*/print_list(division);printf("\n");
         break;
       default:
         printf("Invalid opcode");
     }
    }
   return 0;
 }
