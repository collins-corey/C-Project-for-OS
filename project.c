#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[3];
int counter = 0;
int sharedVar = 100;
pthread_mutex_t lock;
int primes[3];

int isPrime(int number){
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

void* prime_test(void *num){
	int random;
	int prime;
	int val = *(int *) num;
	
	if(val == 1){
		random = rand() % ((999 - 2) + 1) + 2;
		for(int p = random; p < 999; p++){
			int flag = isPrime(p);
			if(flag == 1){
				prime = p;
				break;
			}
		}
	}
	
	else if(val == 2){
		random = rand() % ((2000 - 1000) + 1) + 1000;
		for(int p = random; p < 2000; p++){
			int flag = isPrime(p);
			if(flag == 1){
				prime = p;
				break;
			}
		}
	}
	
	else if(val == 3){
		random = rand() % ((30000 - 20000) + 1) + 20000;
		for(int p = random; p < 30000; p++){
			int flag = isPrime(p);
			if(flag == 1){
				prime = p;
				break;
			}
		}
	}
	
    pthread_mutex_lock(&lock);
	
    printf("\n Thread with ID = %d is entering its critical section and the prime number %d is placed in the shared array.\n", tid[counter++], prime);	
    primes[val] = prime;    
    sleep(5);
	
    pthread_mutex_unlock(&lock);
}

int main(void)
{
    if (pthread_mutex_init(&lock, NULL) != 0) 
    {
        printf("mutex initialization failed\n");
        return 1;
    }
	
	int i = 0;
	while (i < 3){
		int err = pthread_create(&(tid[i]), NULL, &prime_test, &i);
		
		if (err != 0){
			printf("cannot create thread :[%s]\n", strerror(err));
		}
		i++;
	}	
	pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	
    pthread_mutex_destroy(&lock);
	
    return 0;
}