RPCGEN = rpcgen
CC = gcc
CFLAGS = -Wall -pthread -I/usr/include/tirpc
LDFLAGS = -ltirpc


all: task.h client server


task.h: task.x
$(RPCGEN) task.x


client: client.c task_clnt.c task_xdr.c
$(CC) $(CFLAGS) -o client client.c task_clnt.c task_xdr.c $(LDFLAGS)


server: server.c server_impl.c worker.c task_queue.c result_store.c task_svc.c task_xdr.c
$(CC) $(CFLAGS) -o server server.c server_impl.c worker.c task_queue.c result_store.c task_svc.c task_xdr.c $(LDFLAGS)


clean:
rm -f client server task_*.c task.h
