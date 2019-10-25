CC=g++ -O2 -fno-stack-limit -x c++ -std=c++17
APP = yandex-contest-concat

all: build

run_app:
	./$(APP)

build: main.cpp
	$(CC) main.cpp -o $(APP)

build_debug: main.cpp
	$(CC) -DDEBUG main.cpp -o $(APP)

clean:
	rm -rf *.o $(APP)

install:
	install ./$(APP) /usr/local/bin
uninstall:
	rm -rf /usr/local/bin/$(APP)