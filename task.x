struct task {
int id;
int type; // 1, 2, or 3
string payload<256>;
};
struct result {
int id;
string output<256>;
};
program TASKPROG {
version TASKVERS {
int SUBMIT_TASK(task) = 1;
result GET_RESULT(int) = 2;
} = 1;
} = 0x23451111;
