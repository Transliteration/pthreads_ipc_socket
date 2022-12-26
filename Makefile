all: main.cpp build/consumer build/producer build/buffer 
	g++ main.cpp build/consumer build/producer build/buffer -o app1.out -Og -pthread -Werror


build/consumer: consumer/consumer.cpp consumer/consumer.hpp runnable/runnable.hpp buffer
	g++ -c consumer/consumer.cpp -o build/consumer -Og -Werror


build/producer: producer/producer.cpp producer/producer.hpp runnable/runnable.hpp buffer
	g++ -c producer/producer.cpp -o build/producer -Og -Werror


build/buffer: buffer/buffer.cpp buffer/buffer.hpp 
	g++ -c buffer/buffer.cpp -o build/buffer -Og -Werror


clean:
	rm -rf build/*
