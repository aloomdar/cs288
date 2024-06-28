#include <stdio.h>
#define max 100

void radix(unsigned int A[], unsigned int n){
	unsigned int bucket0[n], bucket1[n], mask, count0, count1;
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

void radixSigned(float A[], unsigned int n){
	unsigned int positive[n], negative[n], negCount, posCount;
	negCount = posCount = 0;
	
	unsigned int *ptr = (unsigned int *) A;
	for(int i = 0; i < n; i++){
		if(A[i] >= 0){
			positive[posCount++] = ptr[i];
		}
		else{
			negative[negCount++] = ~ptr[i];
		}
	}
	
	radix(positive, posCount);
	radix(negative, negCount);
	for(int i = negCount - 1; i >=0; i++){
		A[negCount-1 -i] = ~negative[i];
	}
	for(int i = 0; i < posCount; i++){
		A[negCount + i] = positive[i];
	}
	
}

int main(){
	int size, i = 0;
	printf("How many real numbers would you like to enter: \n");
	scanf("%d", &size);

	float A[size], num;

	while(i < size){
		printf("Enter real number: ");
		scanf("%f", &num);
		A[i] = num;
		i++;
	}
	
	printf("Original array\n");
	for(int i = 0; i < size; i++){
		printf("%f ", A[i]);
	}

	radixSigned(A, size);

	printf("Sorted array\n");
	for(int i = 0; i < size; i++){
		printf("%f ", A[i]);
	}
	printf("\n");
}
