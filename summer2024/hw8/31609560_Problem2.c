#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long double PI = 3.14159265358979323846264338327950288419716939937510;
long double sum;
unsigned long n;
unsigned int numThread;

pthread_mutex_t mutex;

void *calculatePi(void *threadID){
	
	long id = (long)threadID;
	long double partialSum = 0.0;

	for(int i = n/numThread * id + 1; i <= n/numThread * (id + 1); i++){
		double x = ((double)i - 0.5)/n;
		partialSum += 4.0 / (1.0 + x * x);
	}
	pthread_mutex_lock(&mutex);
	sum += partialSum;
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	
	if(argc != 3){
		printf("Enter the number of threads and the number of terms: ");
		scanf("%u %lu", &numThread, &n);
	}
	else{
		n = atoi(argv[1]);
		numThread = atoi(argv[2]);
	}

	if(numThread > n){
		printf("Number of threads is greater than number of terms\n");
		return -1;
	}

	pthread_mutex_init(&mutex, NULL);
	pthread_t *thread = malloc(numThread * sizeof(pthread_t));
	
	for(unsigned long i = 0; i < numThread; i++){
		pthread_create(&thread[i], NULL, calculatePi, (void *)i);
	}
		
	for(unsigned long i = 0; i < numThread; i++){
		pthread_join(thread[i], NULL);
	}
	
	free(thread);	

	pthread_mutex_destroy(&mutex);

	long double pi = sum/n;
	printf("Pi approximation is %.22Lf\n", pi);
	
	pthread_exit(NULL);
}
