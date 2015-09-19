 #include <prodcons.h>

 void producer(int32 count)
 {
 	int32 i =0;
 	for (i = 0; i < count; i++) //Code to produce values less than equal to count
 	{
 		n = i; //produced value should get assigned to global variable 'n'
 		printf("produced : %d\n", n); //print produced value e.g. produced : 8
 	}
 	return 0;
 }