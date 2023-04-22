#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_CONCURRENT_THREADS 10
#define MAX_BUFFER_SIZE 100

pthread_mutex_t sensor_data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tv_data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sensor_data_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t tv_data_cond = PTHREAD_COND_INITIALIZER;
char sensor_data[MAX_BUFFER_SIZE][100];
char tv_data[MAX_BUFFER_SIZE][100];
int sensor_data_count = 0;
int tv_data_count = 0;

void* read_sensor_data(void* arg) {
    char* sensor = (char*) arg;
    for (int i = 1; i <= 10; i++) {
        char data[100];
        sprintf(data, "Sensor %s data point %d", sensor, i);
        pthread_mutex_lock(&sensor_data_mutex);
        while (sensor_data_count == MAX_BUFFER_SIZE) {
            pthread_cond_wait(&sensor_data_cond, &sensor_data_mutex);
        }
        strcpy(sensor_data[sensor_data_count], data);
        sensor_data_count++;
        pthread_cond_signal(&sensor_data_cond);
        pthread_mutex_unlock(&sensor_data_mutex);
        usleep(500000); // simulate time-consuming task
    }
    return NULL;
}

void* decode_tv_stream(void* arg) {
    char* stream = (char*) arg;
    for (int i = 1; i <= 10; i++) {
        char data[100];
        sprintf(data, "Decoded data from TV stream %s, frame %d", stream, i);
        pthread_mutex_lock(&tv_data_mutex);
        while (tv_data_count == MAX_BUFFER_SIZE) {
            pthread_cond_wait(&tv_data_cond, &tv_data_mutex);
        }
        strcpy(tv_data[tv_data_count], data);
        tv_data_count++;
        pthread_cond_signal(&tv_data_cond);
        pthread_mutex_unlock(&tv_data_mutex);
        usleep(500000); // simulate time-consuming task
    }
    return NULL;
}

int main() {
    pthread_t sensor_threads[3];
    pthread_t tv_threads[3];

    char* sensor_streams[] = {"Sensor1", "Sensor2", "Sensor3"};
    char* tv_streams[] = {"TVStream1", "TVStream2", "TVStream3"};

    for (int i = 0; i < 3; i++) {
        pthread_create(&sensor_threads[i], NULL, read_sensor_data, (void*) sensor_streams[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_create(&tv_threads[i], NULL, decode_tv_stream, (void*) tv_streams[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(sensor_threads[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(tv_threads[i], NULL);
    }

    printf("Sensor data:\n");
    for (int i = 0; i < sensor_data_count; i++) {
        printf("%s\n", sensor_data[i]);
    }

    printf("TV stream data:\n");
    for (int i = 0; i < tv_data_count; i++) {
        printf("%s\n", tv_data[i]);
    }

    return 0;
}
