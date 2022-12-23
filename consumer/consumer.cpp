#include "Consumer.hpp"

// Поток 2. Должен обрабатывать данные, которые помещаются в общий буфер. После получения данных общий буфер затирается. 
// Поток должен вывести полученные данные на экран, рассчитать  общую  сумму всех  элементов, которые являются численными значениями.  
// Полученную сумму передать в Программу №2. После этого поток ожидает следующие данные.

Consumer::Consumer(std::string &buffer)
: buffer(buffer)
, should_stop(false)
{}

Consumer::run()
{
    while(!should_stop)
	{
        // lock();

        // wait on condition
        // pthread_cond_wait(&m_con, &m_mut);
        // condition fulfilled
        std::cout << "Consumer: Notified on condition!" << std::endl;
        std::cout << "Consumer: Lock aquired!" << std::endl;

        // unlock();


        std::cout << "Consumer: Buffer content: " << buffer << std::endl;

        // inform thread 2 to consume
        std::cout << "Thread 2 informed!" << std::endl;
        // release lock
        std::cout << "Lock released!" << std::endl;
	}
}
