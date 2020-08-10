//Max Heap
#include <stdio.h>
#include <stdlib.h>
#define total 10

void print_array(int num[]);
void adjust(int num[], int root, int length);
void swap(int *a, int *b);

int main(){
	int num[total];
	register int i;
	for(i=0;i<total;i++){
		num[i]=rand()%100;
	}
	printf("Origin: \n");
	print_array(num);

	for(i=1;i<total;i++){
		printf("%d th:\n",i);
		adjust(num,0,i);
	}

	printf("final:\n");
	print_array(num);
	return 0;
}


//test
void print_array(int num[]){
	register int i;
	printf("%d",num[0]);
	for(i=1;i<total;i++){
		printf(", %d",num[i]);
	}
	printf("\n");
}


//Take array as binary tree (level-order traversal).
//Child(ren) of num[i]: num[2i+1] (, num[2i+2]) .
void adjust(int num[], int root, int max_index){
	int left_child, right_child;
	left_child=root*2+1;
	right_child=root*2+2;

	while(left_child <= max_index){
		
		if(right_child <= max_index){
			//find the max of "parent, left, right"
			if(num[left_child] < num[right_child]){
				if(num[root] < num[right_child]){
					swap(&num[root], &num[right_child]);
				}
			}
			else{ // left >= right
				if(num[root] < num[left_child]){
					swap(&num[root], &num[left_child]);
				}
			}
		}

		else{
			if(num[root] < num[left_child]){
				swap(&num[root], &num[left_child]);
			}
		}

		left_child=left_child*2;
		right_child=left_child+1;

		print_array(num);
	}		
}

void swap(int *a, int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}
