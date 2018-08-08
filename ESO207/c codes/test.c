#include<stdio.h>

void bin_search(int start, int end, int *a, int k){

		int mid=(start+end)/2;
			if(end<start){
						printf("Not Found\n");
								return;
									}
				if(a[mid] == k){
							printf("Found at %d\n",mid);
									return;
										}
					if(a[mid] > k){
							 bin_search(start,mid,a,k);
							 	 return;
								 	}else{
											 bin_search(mid+1,end,a,k);
											 	}

}
int main(){
		int n;
			scanf("%d",&n);
				int a[n];
					for(int  i=0;i<n;i++)
								scanf("%d",&a[i]);
						int k;
							scanf("%d",&k);
								bin_search(0,n-1,a,k);
									return 0;
}

