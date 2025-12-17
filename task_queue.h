#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H


#include <pthread.h>
#include "task.h"


typedef struct task_node {
task t;
struct task_node *next;
} task_node;


typedef struct {
task_node *head;
task_node *tail;
pthread_mutex_t mutex;
pthread_cond_t not_empty;
} task_queue;


void queue_init(task_queue *q);
void queue_push(task_queue *q, task t);
void queue_pop(task_queue *q, task *out);


#endif
