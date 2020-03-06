#include <ucontext.h>
#include <unistd.h>
#include <stdio.h>

extern ucontext_t uc_producer;
extern ucontext_t uc_consumer;
extern int product;

void consumer(void)
{
	while (1) {
		sleep(1);
		printf("[consumer] consume %d\n", product);

		swapcontext(&uc_consumer, &uc_producer);
	}
}
