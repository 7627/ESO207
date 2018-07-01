#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

  char nut[20];
  int val,weight,q;
  int max_cal=0;
  scanf("%d",&weight);
  max_cal=10*weight;
  // printf("%d\n",max_cal);
  scanf("%d",&q);
  int i=0;

  for(i=0;i<q;i++){
    scanf("%s",nut);
    scanf("%d",&val);
    if(!strcmp("PROTEIN",nut)){
      max_cal=max_cal-4*val;
      // printf("%d\n",max_cal);
    }
    else if(!strcmp("FAT",nut)){
      max_cal=max_cal-9*val;
      // printf("%d\n",max_cal);
    }
    else if(!strcmp("CARB",nut)){
      max_cal=max_cal-4*val;
      printf("%d\n",max_cal);
    }
    else{
      printf("INVALID Nutrient");
    }
  }
  printf("%d",max_cal);
    return 0;
}
