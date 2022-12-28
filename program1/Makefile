APP_NAME := program1.out

CXXFLAGS := -O3 -Werror

all: $(APP_NAME)

$(APP_NAME): main.cpp build build/consumer build/producer build/buffer 
	$(CXX) main.cpp build/consumer build/producer build/buffer -o $@ $(CXXFLAGS) -pthread 


build/consumer: consumer/consumer.cpp consumer/consumer.hpp runnable/runnable.hpp buffer
	$(CXX) -c consumer/consumer.cpp -o $@ $(CXXFLAGS) 


build/producer: producer/producer.cpp producer/producer.hpp runnable/runnable.hpp buffer
	$(CXX) -c producer/producer.cpp -o $@ $(CXXFLAGS) 


build/buffer: buffer/buffer.cpp buffer/buffer.hpp 
	$(CXX) -c buffer/buffer.cpp -o $@ $(CXXFLAGS) 


build:
	mkdir -p $@


clean:
	rm -f $(APP_NAME)
	rm -rf build/*
	rmdir -p build
