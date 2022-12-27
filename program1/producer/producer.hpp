#include <string>
#include "../buffer/buffer.hpp"
#include "../runnable/runnable.hpp"

class Producer final : public Runnable
{
public:
	Producer(Buffer &buffer);

	void run();
	bool checkInput(const std::string &inputStr);
	std::string transformInput(std::string inputStr);

private:
	Buffer &buffer;
	bool should_stop;
};
