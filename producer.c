#include <ucontext.h>
#include <unistd.h>
#include <stdio.h>

extern ucontext_t uc_producer;
extern ucontext_t uc_consumer;
extern int product;

void producer(void)
{
	for (int i = 1; i < 10000; i++) {
		sleep(1);
		product = i;
		printf("[producer] produce %d\n", product);

		swapcontext(&uc_producer, &uc_consumer);
	}
}
