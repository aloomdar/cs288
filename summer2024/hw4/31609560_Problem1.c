#include <stdio.h>
#define max 100

void radix(unsigned int A[], unsigned int n){
	unsigned int bucket0[max], bucket1[max], mask, count0, count1;
	for(int d = 0; d < 32; d++){
		mask = 1<<d;
		count1 = count0 = 0;
		for(int i = 0; i < n; i++){
			if((A[i]&mask) == 0){
				bucket0[count0++] = A[i];
			}
			else{
				bucket1[count1++] = A[i];
			}
		}
		for(int i = 0; i < count0; i++){
			A[i] = bucket0[i];
		}
		for(int i = 0; i < count1; i++){
			A[count0 + i] = bucket1[i];
		}
	}
}

int main(){
	int size, num, A[max], i = 0;
	printf("How many integers would you like to enter: \n");
	scanf("%d", &size);
	
	while(i < size){
		printf("Enter integer: ");
		scanf("%d", &num);
		A[i] = num;
		i++;
	}
	
	radix(A, size);

	printf("Sorted array\n");
	for(int i = 0; i < size; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}
