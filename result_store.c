#include <string.h>
#include "result_store.h"


void result_store_init(result_store *rs) {
memset(rs->entries, 0, sizeof(rs->entries));
pthread_mutex_init(&rs->mutex, NULL);
}


void result_store_put(result_store *rs, result r) {
pthread_mutex_lock(&rs->mutex);
for (int i = 0; i < MAX_RESULTS; i++) {
if (!rs->entries[i].used) {
rs->entries[i].used = 1;
rs->entries[i].r = r;
break;
}
}
pthread_mutex_unlock(&rs->mutex);
}


int result_store_get(result_store *rs, int id, result *out) {
pthread_mutex_lock(&rs->mutex);
for (int i = 0; i < MAX_RESULTS; i++) {
if (rs->entries[i].used && rs->entries[i].r.id == id) {
*out = rs->entries[i].r;
pthread_mutex_unlock(&rs->mutex);
return 1;
}
}
pthread_mutex_unlock(&rs->mutex);
return 0;
}
