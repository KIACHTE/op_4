#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "task.h"


int main() {
CLIENT *cl = clnt_create("localhost", TASKPROG, TASKVERS, "tcp");
if (!cl) {
clnt_pcreateerror("client");
return 1;
}


while (1) {
task t;
printf("Task type (1=reverse,2=sum,3=fib,0=exit): ");
scanf("%d", &t.type);
if (t.type == 0) break;
getchar();


printf("Payload: ");
fgets(t.payload, 256, stdin);
t.payload[strcspn(t.payload, "\n")] = 0;


int *id = submit_task_1(&t, cl);
printf("Task ID: %d\n", *id);


printf("Get result? (y/n): ");
char c = getchar(); getchar();
if (c == 'y') {
result *r = get_result_1(id, cl);
printf("Result: %s\n", r->output);
}
}


clnt_destroy(cl);
return 0;
}
