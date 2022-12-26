#include <string>
#include "../buffer/buffer.hpp"
#include "../runnable/runnable.hpp"

class Consumer final : public Runnable
{
public:
    Consumer(Buffer &buffer);

    int calculateSum(const std::string &data);

    void run();

private:
    Buffer &buffer;
    bool should_stop;
};