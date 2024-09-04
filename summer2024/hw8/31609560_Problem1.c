#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define max_size 1000

void countSort(int arr[]){
	int count[max_size];
	int outputArr[max_size];
	
	for(int i = 0; i < max_size; i++){
		count[i] = 0;
	}	

	for(int i = 0; i < max_size; i++){
		count[arr[i]]++;
	}

	for(int i = max_size-1; i >= 0; i--){
		outputArr[count[arr[i]]-1] = arr[i];
		count[arr[i]]--;
	}
	for(int i = 0; i < max_size; i++){
		arr[i] = outputArr[i];
	}
}

int main(int argc, char *argv[]){
	int taskid, numtasks;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	char *filename = argv[1];
	FILE *input = fopen(filename, "rb");

	int *arr = (int *) malloc(max_size * sizeof(int));
	int array = fread(arr, sizeof(int), max_size, input);

	fclose(input);

	int *localArr = (int *) malloc(max_size * sizeof(int));
	
	int split = max_size / numtasks;

	
	MPI_Scatter(arr, split, MPI_INT, localArr, split, MPI_INT, 0, MPI_COMM_WORLD);
	printf("scatter is working fine\n");
	countSort(localArr);
	printf("countsort is working fine\n");
	MPI_Gather(localArr, split, MPI_INT, arr, split, MPI_INT, 0, MPI_COMM_WORLD);
	printf("gather is working fine.\n");
	MPI_Barrier(MPI_COMM_WORLD);
	for(int i =0; i < max_size; i++){
		printf("%d\n", arr[i]);
	}
	printf("End of sorted array\n");

	if (taskid == 0){
		FILE *output = fopen("sorted_output", "wb");
		printf("opened file successfully\n");
		fwrite(arr, sizeof(int), max_size, output);
		printf("written to file succesfully\n");
		fclose(output);
		printf("closed file successfully\n");
	}
	

	free(arr);
	free(localArr);

	MPI_Finalize();
	return 0;
}
