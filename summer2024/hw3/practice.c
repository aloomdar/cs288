#include <stdio.h>
#include <stdlib.h>

int main(){

	FILE *f1, *f2, *result;
	int dim1, dim2;
	
	f1 = fopen("100dmat.bin", "rb");
	f2 = fopen("100dmat2.bin", "rb");
	result = fopen("result.bin", "wb");

	fread(&dim1, sizeof(dim1), 1, f1);
	fread(&dim2, sizeof(dim2), 1, f2);
	
	if(dim1 != dim2 || dim1 > 100 || dim2 > 200){
		printf("Matrix dimensions are not the same or they are greater than 100\n");
		return -1;
	}	

	int ***mat1 = (int ***) malloc(dim1 * sizeof(int**));
	int ***mat2 = (int ***) malloc(dim1 * sizeof(int**));
	long long ***resmat = (long long ***) malloc(dim1 * sizeof(long long **));

	for(int i = 0; i < dim1; i++){
		mat1[i] = (int **) malloc(dim1 * sizeof(int *));
		mat2[i] = (int **) malloc(dim1 * sizeof(int *));
		resmat[i] = (long long **) malloc(dim1 * sizeof(long long *));
		for(int j = 0; j < dim1; j++){
			mat1[i][j] = (int *) malloc(dim1 * sizeof(int));
                	mat2[i][j] = (int *) malloc(dim1 * sizeof(int));
                	resmat[i][j] = (long long *) malloc(dim1 * sizeof(long long));
			for(int k = 0; k < dim1; k++){
				fread(&mat1[i][j][k], sizeof(int), 1, f1);
				fread(&mat2[i][j][k], sizeof(int), 1, f2);
			}
		}
	}
	fclose(f1);
	fclose(f2);
	
	for(int i = 0; i < dim1; i++){
	    	for(int j = 0; j < dim1; j++){
            		for (int k = 0; k < dim1; k++){
				resmat[i][j][k] = (long long)mat1[i][j][k] * (long long)mat2[i][j][k];
				fwrite(&resmat[i][j][k], sizeof(long long), 1, result);
            		}
			free(mat1[i][j]);
			free(mat2[i][j]);
			free(resmat[i][j]);
        	}
		free(mat1[i]);
		free(mat2[i]);
		free(resmat[i]);
    	}
	
	fclose(result);
	return 0;
}
