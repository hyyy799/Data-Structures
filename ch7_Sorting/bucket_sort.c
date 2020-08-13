//Stable
//Distribution Sort

#include <stdio.h>
#include <stdlib.h>
#define total 15
#define basic 10

void print_array(int num[]);
void print_bucket(int bucket[basic][total], int record[basic]);
void bucket_sort(int num[]);

int main(){
	int num[total];
	register int i;

	for(i=0;i<total;i++){
		num[i]=rand()%10000;
	}
	printf("origin:\n");
	print_array(num);

	bucket_sort(num);

	printf("===\nfinal:\n");
	print_array(num);

	return 0;
}

void print_array(int num[]){
	register int i;
	printf("%d",num[0]);
	for(i=1;i<total;i++){
		printf(" %d",num[i]);
	}
	printf("\n");
}

void print_bucket(int bucket[basic][total], int record[basic]){
	register int i, j;
	for(i=0;i<basic;i++){
		printf("%d | ",i);
		for(j=0;j<record[i];j++){
			printf("%d ", bucket[i][j]);
		}
		printf("\n");
	}
}

void bucket_sort(int num[]){
	int bucket[basic][total]={0};
	int record[basic]={0}; // how many numbers in one bucket
	
	int n; // for digit
	int digit;
	register int i,j,k;

	//LSD
	n=1;
	while(n<10000){
		//put them into bucket
		for(i=0;i<total;i++){
			digit= (num[i]/n)%10;
			bucket[digit][record[digit]] = num[i]; 
			//record[digit] value: how many number in bucket[digit]
			record[digit]++;
		}

		printf("===\nPut into bucket!\n");
		print_bucket(bucket, record);

		//A
		//put them back to num[]
		//i for num[], j, k for bucket[j][k]
		i=0;
		for(j=0;j<total;j++){
			if(record[j]==0)
				continue;
			for(k=0;k<record[j];k++){
				num[i]=bucket[j][k];
				i++;
			}
			record[j]=0; //reset
		}

		printf("===\nPut back to num[]!\n");
		print_array(num);

		n*=10;
	}
}
