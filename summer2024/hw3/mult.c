#include <stdio.h>
#include <stdlib.h>

int main(){
	
	FILE *f1, *f2;
	int dim1, dim2;
	int elem1, elem2;
	
	f1 = fopen("matrix1.bin", "rb");
	f2 = fopen("matrix2.bin", "rb");
	
	fread(&dim1, sizeof(dim1), 1, f1);
	fread(&elem1, sizeof(elem1), 1, f1);
	fread(&dim2, sizeof(dim2), 1, f2);
	fread(&elem2, sizeof(elem2), 1, f2);
	
	printf("Size of mat1: %d First element: %d\n", dim1, elem1);
	printf("Size of mat2: %d First element: %d\n", dim2, elem2);
	long long int result;
	result = (long long int) elem1 * (long long int) elem2;
	printf("Product of first two elements: %lld\n", result);
	return 0;
}
