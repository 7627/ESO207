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
   head=temp;
   return head;
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
  while(temp!=NULL){
    printf("%d",temp->digit);
    temp=temp->next;
  }
  printf("\n");
}


struct node* add(struct node* number1,struct node* number2){
  struct node* result=NULL;
  int carry=0;
  while(number1!=NULL & number2!=NULL){
    result=insert_at_front(result,(number1->digit+number2->digit+carry)%10);
    carry=(number1->digit+number2->digit+carry)/10;
    number1=number1->next;
    number2=number2->next;
  }
  while(number1!=NULL){
    result=insert_at_front(result,(number1->digit+carry)%10);
    carry=(number1->digit+carry)/10;
    number1=number1->next;
  }
  while(number2!=NULL){
    result=insert_at_front(result,(number2->digit+carry)%10);
    carry=(number2->digit+carry)/10;
    number2=number2->next;
  }
  result= (carry==1)? insert_at_front(result,carry):result;
  return result;
}
  // printf("1");
  // struct node* result=NULL;
  // int carry=0;
  // printf("2");
  // while(number1!=NULL & number2!=NULL){
  //   // result=calloc(1,sizeof(struct node));
  //   // result->digit=(number1->digit+number2->digit+carry)%10;
  //   printf("3");
  //   result=insert_at_front(result,(number1->digit+number2->digit+carry)%10);
  //   printf("4");
  //   carry=(number1->digit+number2->digit+carry)/10;
  //   number1=number1->next;
  //   number2=number2->next;
  //   printf("%d",result->digit);
  //   // result=result->next;
  // }
  // while(number1!=NULL){
  //   // result=calloc(1,sizeof(struct node));
  //   // result->digit=(number1->digit+carry)%10;
  //   result=insert_at_front(result,(number1->digit+carry)%10);
  //   carry=(number1->digit+carry)/10;
  //   number1=number1->next;
  //   printf("%d",result->digit);
  //   // result=result->next;
  // }
  // while(number2!=NULL){
  //   // result=calloc(1,sizeof(struct node));
  //   // result->digit=(number2->digit+carry)%10;
  //   result=insert_at_front(result,(number1->digit+carry)%10);
  //   carry=(number2->digit+carry)/10;
  //   number2=number2->next;
  //   printf("%d",result->digit);
  //   // result=result->next;
  // }
  // return result;

struct node* subtract(struct node* number1, struct node* number2){
  struct node* result=NULL;
  int carry=0;
  while(number1!=NULL, number2!=NULL){
    if(number1->digit - carry>=number2->digit){
      result=insert_at_front(result,number1->digit - number2->digit - carry);
      carry=0;
    }
    else{
      result=insert_at_front(result,number1->digit - carry - number2->digit + 10);
      carry=1;
    }
    number1=number1->next;
    number2=number2->next;
  }
  while(number1!=NULL){
    result=insert_at_front(result,number1->digit - carry);
    carry=0;
    number1=number1->next;
  }
  // while(number2!=NULL){
  //   result=
  // }
  return result;
}

// struct node* multiply(struct node* number1, struct node* number2,int n1, int n2){
//   struct node* result[n2];
//   int i=0;
//
// }

 int main(){
   int n1,n2,x;
   scanf("%d %d",&n1,&n2); //n1 and n2 are the number of digits in number1 and number2 resp.
   struct node* number1,*number2;
   int i=0;
   getchar();
   number1=scan_number(n1);
   getchar();
   number2=scan_number(n2);
   print_list(number1);
   print_list(number2);
   struct node* addition=NULL;
   // addition=insert_at_front(addition,2);
   // addition=insert_at_front(addition,3);
   // print_list(addition);
   addition=add(number1,number2);

   print_list(addition);
   printf("done");
   return 0;
 }
