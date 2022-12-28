APP_NAME := program2.out

CXXFLAGS := -O3 -Werror

all: $(APP_NAME)

$(APP_NAME): main.cpp build build/server
	$(CXX) main.cpp build/server -o $@ $(CXXFLAGS) 

build/server: server/server.cpp server/server.hpp 
	$(CXX) -c server/server.cpp -o $@ $(CXXFLAGS) 

build:
	mkdir -p $@

clean:
	rm -f $(APP_NAME)
	rm -rf build/*
	rmdir -p build