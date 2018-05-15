#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

volatile int running = 0;
pthread_mutex_t running_mutex;

void *ssort(void *ptr) {
	unsigned int d = *((unsigned int *) ptr);
	sleep(d);
	printf("%d ", d);

	pthread_mutex_lock(&running_mutex);
	running--;
	pthread_mutex_unlock(&running_mutex);

	return NULL;
}

int main(int argc, char **argv) {
	pthread_mutex_init(&running_mutex, NULL);

	int data[10] = {5,1,9,6,2,8,7,3,4};
	for (int i=0; i < 10; i++) {
		// über mutex erhöhen
		pthread_mutex_lock(&running_mutex);
		running++;
		pthread_mutex_unlock(&running_mutex);

		// thread starten
		pthread_t t;
		pthread_create(&t, NULL, ssort, (void *) &data[i]);
	}

	while (running > 0) {
		sleep(1);
	}
	pthread_mutex_destroy(&running_mutex);
	
	return 0;
}
