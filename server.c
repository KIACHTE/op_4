#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <rpc/rpc.h>
#include "task_queue.h"
#include "result_store.h"


extern void *worker_thread(void *arg);


task_queue g_queue;
result_store g_results;
int g_next_id = 1;
pthread_mutex_t id_mutex = PTHREAD_MUTEX_INITIALIZER;


int main() {
queue_init(&g_queue);
result_store_init(&g_results);


pthread_t workers[3];
for (int i = 0; i < 3; i++)
pthread_create(&workers[i], NULL, worker_thread, NULL);


svc_run();
fprintf(stderr, "svc_run returned unexpectedly\n");
exit(1);
}
