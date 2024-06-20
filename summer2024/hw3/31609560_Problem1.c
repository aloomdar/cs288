#include <stdio.h>
#include <stdlib.h>

int main(){

	FILE *f1, *f2, *result;
	int dim1, dim2;
	
	f1 = fopen("100dmat.bin", "rb");
	f2 = fopen("100dmat2.bin", "rb");

	fread(&dim1, sizeof(dim1), 1, f1);
	fread(&dim2, sizeof(dim2), 1, f2);
	
	printf("Size of matrix1: %d\n", dim1);
	printf("Size of matrix2: %d\n", dim2);

	if(dim1 != dim2 || dim1 > 100 || dim2 > 200){
		printf("Matrix dimensions are not the same or they are greater than 100\n");
		return 0;
	}	

	int size = dim1 * dim1 * dim1;
	printf("Total number of elements: %d\n", size);

	int mat1[dim1][dim1][dim1];
	int mat2[dim1][dim1][dim1];
	long long resmat[dim1][dim1][dim1];

	for(int i = 0; i < dim1; i++){
		for(int j = 0; j < dim1; j++){
			for(int k = 0; k < dim1; k++){
				fread(&mat1[i][j][k], sizeof(mat1), 1, f1);
				fread(&mat2[i][j][k], sizeof(mat2), 1, f2);
				printf("Elem mat1: %d\n", mat1[i][j][k]);
				printf("Elem mat2: %d\n", mat2[i][j][k]);
			}
		}
	}
	fclose(f1);
	fclose(f2);
	
	printf("Elements in result 3d array/matrix\n");
	printf("----------------------------------\n");
	for(int i = 0; i < dim1; i++){
	    for(int j = 0; j < dim1; j++){
            for (int k = 0; k < dim1; k++){
				resmat[i][j][k] = (long long)mat1[i][j][k] * (long long)mat2[i][j][k];
				printf("Resultants: %lld\n", resmat[i][j][k]);
            }
        }
    }
	
	return 0;
}
