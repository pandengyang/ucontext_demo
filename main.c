#include <ucontext.h>
#include <stdio.h>

ucontext_t uc_main;
ucontext_t uc_producer;
ucontext_t uc_consumer;

int product;
char stack_producer[1024 * 16];
char stack_consumer[1024 * 16];

void producer(void);
void consumer(void);

int main(int argc, char **argv)
{
	getcontext(&uc_producer);
	uc_producer.uc_stack.ss_sp = stack_producer;
	uc_producer.uc_stack.ss_size = sizeof stack_producer;
	makecontext(&uc_producer, producer, 0);

	getcontext(&uc_consumer);
	uc_consumer.uc_stack.ss_sp = stack_consumer;
	uc_consumer.uc_stack.ss_size = sizeof stack_consumer;
	makecontext(&uc_consumer, consumer, 0);

	swapcontext(&uc_main, &uc_producer);
}
