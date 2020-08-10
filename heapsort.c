#include <stdio.h>
#include <stdlib.h>
#define total 10

void print_array(int num[]);
void max_heap(int num[], int root, int length);
void heap_sort(int num[], int max_index);
void swap(int *a, int *b);

int main(){
	int num[total];
	register int i;
	for(i=0;i<total;i++){
		num[i]=rand()%100;
	}
	printf("Origin: \n");
	print_array(num);

	heap_sort(num, total-1);

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
//array[0 to max_index]
//Child(ren) of num[i]: num[2i+1] (, num[2i+2]) .

void max_heap(int num[], int root, int max_index){
	int left_child, right_child;
	left_child=root*2+1;
	right_child=root*2+2;

	if(left_child > max_index)
		return;
	

	//find the biggest of num[root], num[left], num[right]
	int biggest=root;
	if(num[left_child] > num[biggest])
		biggest=left_child;
	if(right_child <= max_index && num[right_child] > num[biggest])
		biggest=right_child;

	if(biggest!=root){
		swap(&num[root], &num[biggest]);
		max_heap(num, biggest, max_index); //Deal with sub-tree.
	}

	print_array(num);
}

//sift down
void heap_sort(int num[], int max_index){
	register int i;

	//from bottom to top
	for(i=max_index/2;i>=0;i--){ // num[i] is non-leaf
		printf("index from %d to %d:\n", i, max_index);
		max_heap(num, i, max_index);
	}

	printf("\nStart to sift down!\n");
	//put the root (biggest value) to the final one (sorted)
	int tmp_index = max_index;
	for(i=max_index;i>=1;i--){
		swap(&num[0], &num[i]);
		tmp_index--;
		max_heap(num, 0, tmp_index);
	}
}

void swap(int *a, int *b){
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}
