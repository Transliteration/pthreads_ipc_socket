#include "consumer.hpp"
#include <iostream>
#include <numeric>

Consumer::Consumer(Buffer &buffer)
    : buffer(buffer), should_stop(false)
{
}

int Consumer::calculateSum(const std::string &data)
{
    auto convertCharToNumber = [](const unsigned char ch)
    {
        if (std::isdigit(ch))
            return ch - '0';
        else
            return 0;
    };

    return std::transform_reduce(std::begin(data), std::end(data), 0, std::plus<>(), convertCharToNumber);
}

void Consumer::run()
{
    while (!should_stop)
    {
        buffer.lock();
        buffer.wait();

        auto buffer_string = buffer.consumeData();

        int sum = calculateSum(buffer_string);

        buffer.unlock();
    }

    // unreachable
    pthread_exit(nullptr);
}
