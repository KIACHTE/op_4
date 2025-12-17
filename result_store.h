#ifndef RESULT_STORE_H
#define RESULT_STORE_H


#include <pthread.h>
#include "task.h"


#define MAX_RESULTS 1024


typedef struct {
int used;
result r;
} result_entry;


typedef struct {
result_entry entries[MAX_RESULTS];
pthread_mutex_t mutex;
} result_store;


void result_store_init(result_store *rs);
void result_store_put(result_store *rs, result r);
int result_store_get(result_store *rs, int id, result *out);


#endif
