#include <stdio.h>
#include <stdlib.h>

int main(){

	FILE *f1, *f2, *result;
	int dim1, dim2;
	
	f1 = fopen("matrix1.bin", "rb");
	f2 = fopen("matrix2.bin", "rb");

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
	
	int *** mat1[dim1][dim1][dim1];
	int *** mat2[dim2][dim2][dim2];
	long long int *** resmat[dim1][dim1][dim1];

	for(int i = 0; i < dim1; i++){
		for(int j = 0; j < dim1; j++){
			for (int k = 0; k < dim1; k++){
				mat1[i][j][k] = (int ***) malloc(dim1 * sizeof(int **));
				mat2[i][j][k] = (int ***) malloc(dim1 * sizeof(int **));
				fread(&mat1[i][j][k], sizeof(mat1), 1, f1);
				fread(&mat2[i][j][k], sizeof(mat2), 1, f2);
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
				resmat[i][j][k] = (long long int ***) malloc(dim1 * sizeof(int **));
				resmat[i][j][k] = (int)mat1[i][j][k] * (int)mat2[i][j][k];
				printf("Resultants: %lld\n", ***resmat[i][j][k]);
				free(mat1[i][j][k]);
				free(mat2[i][j][k]);
				free((void *)resmat[i][j][k]);
            }
        }
    }
	
	return 0;
}
