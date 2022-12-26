#include "buffer.hpp"
#include <iostream>

Buffer::Buffer()
    : readyToConsume(false)
{
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&inputProduced, nullptr);
}

void Buffer::lock()
{
    pthread_mutex_lock(&mutex);
}

void Buffer::unlock()
{
    pthread_mutex_unlock(&mutex);
}

void Buffer::wait()
{
    // check for spirious wakeup
    while (!readyToConsume)
    {
        pthread_cond_wait(&inputProduced, &mutex);
    }

    readyToConsume = false;
}

void Buffer::signal()
{
    pthread_cond_signal(&inputProduced);
}

std::string Buffer::consumeData()
{
    auto temp_buffer = std::move(data);
    readyToConsume = false;
    return temp_buffer;
}

void Buffer::setData(std::string new_data)
{
    data = std::move(new_data);
    readyToConsume = true;
}
