#include <xinu.h>
#include <stddef.h>
#include <stdio.h>

   /*Global variable for producer consumer*/
   extern int32 A[15]; /*this is just declaration*/
   extern int32 prod;
   extern int32 con;
   extern sid32 consumed;
   extern sid32 produced;

  /*function Prototype*/
 void bb_consumer(int32 count, sid32 consumed, sid32 produced);
 void bb_producer(int32 count, sid32 consumed, sid32 produced);