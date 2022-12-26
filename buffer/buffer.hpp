#pragma once
#include <string>
#include <pthread.h>

class Buffer
{
    std::string data;
    pthread_mutex_t mutex;
    pthread_cond_t inputProduced;
    bool readyToConsume;

public:
    Buffer();

    void lock();
    void unlock();

    void wait();
    void signal();

    std::string consumeData();
    void setData(std::string new_data);
};