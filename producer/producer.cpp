#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>


// Должна состоять из двух потоков и одного общего буфера. 
// Поток 1.  Принимает строку, которую введет пользователь.   
// Должна быть проверка, что строка состоит только из цифр и не превышает 64 символа. 
// После проверки строка должна быть отсортирована по убыванию и все элементы, значение которых чётно, заменены на латинские буквы «КВ». 
// После данная строка помещается в общий буфер и поток должен ожидать дальнейшего ввода пользователя.

// xxx

// Поток 2. Должен обрабатывать данные, которые помещаются в общий буфер. После получения данных общий буфер затирается. 
// Поток должен вывести полученные данные на экран, рассчитать  общую  сумму всех  элементов, которые являются численными значениями.  
// Полученную сумму передать в Программу №2. После этого поток ожидает следующие данные.

// Примечание №1 по Программе №1: Взаимодействие потоков должно быть синхронизировано,  поток №2  не должен постоянно опрашивать общий буфер. 
// Механизм синхронизации не должен быть глобальной переменной.

// Примечание №2 по Программе №1: Работа программы должна быть максимально независима от статуса запуска программы №2. 
// Это значит, что внезапный останов программы №2 не должен приводить к немедленным проблемам ввода у пользователя.
// При перезапуске программы №2 необходимо произвести передподключение.

class Producer
{
	std::string &buffer;
	bool should_stop;

public:
	Producer(std::string &buffer)
	: buffer(buffer)
	, should_stop(false)
	{}

	void run()
	{
		std::string user_input;

		while(!should_stop)
		{
			std::cout << "Input your string: ";
			std::getline(std::cin, user_input);

			if (checkInput(user_input))
			{
				// aquire lock
				std::cout << "Lock aquired!" << std::endl;

				std::cout << "Buffer content: " << buffer << std::endl;
				buffer = transformInput(std::move(user_input));
				std::cout << "Transformed buffer content: " << buffer << std::endl;

				// inform thread 2 to consume
				std::cout << "Thread 2 informed!" << std::endl;
				// release lock
				std::cout << "Lock released!" << std::endl;
			}
		}
	}

	bool checkInput(const std::string &inputStr)
	{
		bool containsOnlyDigits = inputStr.find_first_not_of("0123456789") == std::string::npos;
		bool lengthCheck = inputStr.length() <= 64;

		if (!containsOnlyDigits)
		{
			std::cout << "Your input does not consist entirely of numbers!" << std::endl;
		}

		if (!lengthCheck)
		{
			std::cout << "Your input string contains more then 64 symbols!" << std::endl;    
		}
		

		return containsOnlyDigits && lengthCheck;
	}

	std::string transformInput(std::string &&inputStr)
	{
		std::stringstream transformedInput;

		std::sort(std::begin(inputStr), std::end(inputStr), [](const char a, const char b){
			return a > b;
		});  


		for (auto &ch : inputStr)
		{
			if ((ch - '0') % 2 == 0)
			{
				transformedInput << "KB";
			}
			else
			{
				transformedInput << ch;
			}
		}

		return transformedInput.str();
	}
};


int main()
{
	std::string buffer;

	Producer producer(buffer);

	producer.run(); 
}