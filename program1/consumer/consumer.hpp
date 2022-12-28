#include <string>
#include <queue>
#include "../buffer/buffer.hpp"
#include "../runnable/runnable.hpp"

class Consumer final : public Runnable
{
public:
    Consumer(Buffer &buffer);

    int calculateSum(const std::string &data);

    void run();

    bool connectToServerAndSendData(const std::string &data);

private:
    Buffer &buffer;
    std::queue<std::string> unsent_messages;
};
