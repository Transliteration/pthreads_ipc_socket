#include <pthread.h>
#include <string>

#include "producer/producer.hpp"
#include "consumer/consumer.hpp"
#include "runnable/runnable.hpp"
#include "buffer/buffer.hpp"

void *startRunnable(void *data)
{
	Runnable *runnable = static_cast<Runnable *>(data);
	if (runnable)
	{
		runnable->run();
	}

	return nullptr;
}

int main()
{
	Buffer buffer;

	pthread_t thread_producer;
	pthread_t thread_consumer;
	Producer *producer = new Producer(buffer);
	Consumer *consumer = new Consumer(buffer);

	pthread_create(&thread_producer, nullptr, &startRunnable, static_cast<void *>(producer));
	pthread_create(&thread_consumer, nullptr, &startRunnable, static_cast<void *>(consumer));
	pthread_join(thread_producer, nullptr);
	pthread_join(thread_consumer, nullptr);

	delete producer;
	delete consumer;

	return 0;
}
