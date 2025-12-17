#include <stdlib.h>
#include "task_queue.h"


void queue_init(task_queue *q) {
q->head = q->tail = NULL;
pthread_mutex_init(&q->mutex, NULL);
pthread_cond_init(&q->not_empty, NULL);
}


void queue_push(task_queue *q, task t) {
task_node *n = malloc(sizeof(task_node));
n->t = t;
n->next = NULL;


pthread_mutex_lock(&q->mutex);
if (q->tail)
q->tail->next = n;
else
q->head = n;
q->tail = n;
pthread_cond_signal(&q->not_empty);
pthread_mutex_unlock(&q->mutex);
}


void queue_pop(task_queue *q, task *out) {
pthread_mutex_lock(&q->mutex);
while (q->head == NULL)
pthread_cond_wait(&q->not_empty, &q->mutex);


task_node *n = q->head;
q->head = n->next;
if (!q->head)
q->tail = NULL;
*out = n->t;
free(n);
pthread_mutex_unlock(&q->mutex);
}
