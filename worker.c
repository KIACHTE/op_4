#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "task_queue.h"
#include "result_store.h"


extern task_queue g_queue;
extern result_store g_results;


static void process_task(task *t, result *r) {
r->id = t->id;


if (t->type == 1) {
int len = strlen(t->payload);
for (int i = 0; i < len; i++)
r->output[i] = t->payload[len - i - 1];
r->output[len] = '\0';
}
else if (t->type == 2) {
int sum = 0;
char buf[256];
strcpy(buf, t->payload);
char *p = strtok(buf, " ");
while (p) {
sum += atoi(p);
p = strtok(NULL, " ");
}
sprintf(r->output, "%d", sum);
}
else if (t->type == 3) {
int n = atoi(t->payload);
long a = 0, b = 1;
for (int i = 0; i < n; i++) {
long tmp = a + b;
a = b;
b = tmp;
}
sprintf(r->output, "%ld", a);
}
else {
strcpy(r->output, "INVALID");
}
}


void *worker_thread(void *arg) {
task t;
result r;
while (1) {
queue_pop(&g_queue, &t);
process_task(&t, &r);
result_store_put(&g_results, r);
}
return NULL;
}
