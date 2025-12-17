#include <string.h>
#include <pthread.h>
#include "task.h"
#include "task_queue.h"
#include "result_store.h"


extern task_queue g_queue;
extern result_store g_results;
extern int g_next_id;
extern pthread_mutex_t id_mutex;


int *submit_task_1_svc(task *t, struct svc_req *req) {
static int id;
pthread_mutex_lock(&id_mutex);
id = g_next_id++;
pthread_mutex_unlock(&id_mutex);


t->id = id;
queue_push(&g_queue, *t);
return &id;
}


result *get_result_1_svc(int *id, struct svc_req *req) {
static result r;
r.id = *id;
if (!result_store_get(&g_results, *id, &r))
strcpy(r.output, "PENDING");
return &r;
}
