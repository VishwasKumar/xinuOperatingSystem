#include <prodcons.h>


uint net_producer(future *fut, int32 slot, char *str){

	int	retval;
	uint32 target_ip, locport = 8000;


	retval = udp_send(slot,str,strlen(str));
	if (retval == SYSERR) {
			fprintf(stderr, "error sending UDP \n");
			return 1;
		}
	else
		printf("Message sent is: %s\n", str);
	
	retval = udp_recv(slot,response,SIZE,15000);
	if (retval == TIMEOUT) {
			fprintf(stderr, "timeout...\n");
	} else if (retval == SYSERR) {
		fprintf(stderr, "error from udp_recv \n");
		udp_release(slot);
		return 1;
	}
	else
		printf("\n Response Received is %s\n",response);
	
  	future_set(fut, &response);
  	return OK;
}