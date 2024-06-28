#include <stdio.h>
#define MAX_SIZE 100

void radix_sort(unsigned int A[], unsigned int n);

void radix_sort_signed(int A[], int n){
	//separate + and - 
	//radix sort on + based on low 31 bits
	//radix sort on - based on low 31 bits (both ascending)
	//join the buckets
	//Negative first then positive
	
	int positive[MAX_SIZE], negative[MAX_SIZE];
	int pos_count = 0, neg_count = 0;
	//radix sort based on low 31 bits
	for (int i = 0; i < n; i++){
		if (A[i] >= 0){
			positive[pos_count++] = A[i];
		}
		else{
			negative[neg_count++] = ~A[i]; // negating to maintain the original correct order 
		}
		radix_sort(positive, pos_count);
		radix_sort(negative, neg_count); //this is sorting the negative numbers, but because we negated it earlier, technically it's sorting positive numbers

		for (int i = neg_count - 1; i >= 0; i--){ //re-negating to maintain original format. expect this question on the exam
			A[neg_count-1 -i] = ~negative[i]; //as we are looping through the negative numbers, we are sorting it in reverse order ie. if the original array is [1, 3, 5, 7], it becomes [7, 5, 3, 1]
		} 
		for (int i = 0; i < pos_count; i++){
			A[neg_count + i] = positive[i];
		}

	}
}

void radix_sort(unsigned int A[], unsigned int n){
	unsigned int bucket0[MAX_SIZE], bucket1[MAX_SIZE];
	unsigned int mask, count0, count1;
	for(int d = 0; d < 32; d++){
		mask = 1 << d;
		count0 = count1 = 0;
		for (int i = 0; i < n; i++){
			if((A[i] & mask) == 0){
				bucket0[count0++] = A[i]; // if bit is 0, we are adding it to bucket0 and incrementing the index of bucket0
			}
			else{
				bucket1[count1++] = A[i]; // if bit is 1, we are adding it to bucket1 and incrementing the index of bucket1
			}
		}
		for(int i = 0; i < count0; i++){
			A[i] = bucket0[i];
		}
		for (int i = 0; i < count1; i++){
			A[count0 + i] = bucket1[i]; // because we added bucket 0 to array A, we need to start from the index after bucket0 has been added, which is index=count0
		}
	}
}

int main(){
        printf("How many real numbers would you like to enter: ");
	int size;
	scanf("%d", &size);
	int i = 0;
	float arr[size];
	while(i < size){
		printf("Enter a real number: ");
		float num;
		scanf("%f", &num);
		arr[i] = num;
		i++;
	}
        unsigned int *p = (unsigned int *) arr;

	printf("The original array is: ");
	for (int i = 0; i < size; i++){
		printf("%.2f ", arr[i]);
	}

	radix_sort_signed(p, size);
	printf("\nThe sorted array is: ");
	for (int i = 0; i < size; i++){
		printf("%.2f ", arr[i]);
	}
	printf("\n");
}


