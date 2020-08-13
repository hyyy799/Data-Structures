//Stable (because of bucket sort)
//Distribution Sort
//Note: Bucket sort:1 key, Radix sort:1 or 1+ key

//Sorting poker card. min:1, max:13/ min:C, max:S/ C2 > S1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define total 10
#define basic 13
#define suit_mode 1
#define num_mode 2

struct card{
	char suit; //Clover:C, Diamond:D, Heart:H, Spade:S
	int num;
};

struct card data[total];
struct card bucket[basic][total];
int record[basic]={0}; // how many array in bucket[i]

void print_data();
void print_bucket(int mode);
void bucket_sort();

int main(){
	register int i;
	int tmp;

	for(i=0;i<total;i++){
		tmp=rand()%4;
		switch(tmp){
				case 0: 
					data[i].suit='C';
					break;
				case 1:
					data[i].suit='D';
					break;
				case 2:
					data[i].suit='H';
					break;
				case 3:
					data[i].suit='S';
					break;
		}

		data[i].num=rand()%13 +1;
	}

	printf("origin:\n");
	print_data(data);

	//key: num > suit, bucket sort LSD 
	bucket_sort(data);

	printf("===\nfinal:\n");
	print_data(data);

	return 0;
}

void print_data(){
	register int i;
	printf("%c%d", data[0].suit, data[0].num);
	for(i=1;i<total;i++){
		printf("\t%c%d", data[i].suit, data[i].num);
	}
	printf("\n");
}

void print_bucket(int mode){
	register int i, j;

	if(mode==suit_mode){
		for(i=0;i<4;i++){
			switch(i){
				case 0: 
					printf("C |");
					break;
				case 1:
					printf("D |");
					break;
				case 2:
					printf("H |");
					break;
				case 3:
					printf("S |");
					break;
				default:
					printf("wrong!\n");
			}
			for(j=0;j<record[i];j++){
				printf("\t%c%d", bucket[i][j].suit, bucket[i][j].num);
			}
			printf("\n");
		}
	}

	else if(mode==num_mode){
		for(i=0;i<13;i++){
			printf("%d |",i+1);
			for(j=0;j<record[i];j++){
				printf("\t%c%d", bucket[i][j].suit, bucket[i][j].num);
			}
			printf("\n");
		}
	}
}

void bucket_sort(){
		memset(record, 0, basic);
		register int i,j,k;

		//=====suit mode=====//
		//put them into bucket
		for(i=0;i<total;i++){
			switch(data[i].suit){
				case 'C': 
					bucket[0][ record[0] ].suit = data[i].suit;
					bucket[0][ record[0] ].num = data[i].num;
					record[0]++;
					break;
				case 'D':
					bucket[1][ record[1] ].suit = data[i].suit;
					bucket[1][ record[1] ].num = data[i].num;
					record[1]++;
					break;
				case 'H':
					bucket[2][ record[2] ].suit = data[i].suit;
					bucket[2][ record[2] ].num = data[i].num;
					record[2]++;
					break;
				case 'S':
					bucket[3][ record[3] ].suit = data[i].suit;
					bucket[3][ record[3] ].num = data[i].num;
					record[3]++;
					break;
				default:
					printf("wrong!\n");
			}
		}
		printf("===\nPut them into bucket.\n");
		print_bucket(suit_mode);

		//Put them back to data[]
		i=0;
		for(j=0;j<4;j++){
			for(k=0;k<record[j];k++){
				data[i].suit = bucket[j][k].suit;
				data[i].num = bucket[j][k].num;
				i++;
			}
			record[j]=0; //reset
		}
		printf("===\nPut back to data[].\n");
		print_data(data);
		

		//=====num mode =====//
		//put them into bucket
		int tmp_num;
		for(i=0;i<total;i++){
			tmp_num=data[i].num-1;
			bucket[tmp_num][record[tmp_num]].suit = data[i].suit;
			bucket[tmp_num][record[tmp_num]].num = data[i].num; 
			record[tmp_num]++;
		}
		printf("===\nPut them into bucket.\n");
		print_bucket(num_mode);

		//Put them back to data[]
		i=0;
		for(j=0;j<13;j++){
			for(k=0;k<record[j];k++){
				data[i].suit = bucket[j][k].suit;
				data[i].num = bucket[j][k].num;
				i++;
			}
			record[j]=0; //reset
		}
		printf("===\nPut back to data[].\n");
		print_data(data);
}