#include <prodcons.h>


uint net_consumer(future *fut){
  char *i = &fut->value;
  int status;
  status = future_get(fut, &i);
  if (status < 1) {
    printf("future_get failed\n");
    return -1;
  }
	kprintf("Consumer received: %s\n", response);
  return OK;
}
