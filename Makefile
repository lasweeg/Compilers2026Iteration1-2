.PHONY: all run clean

all:
	mkdir -p build
	bison -d -o build/parser.cpp grammar/parser.y
	flex -o build/scanner.cpp grammar/scanner.l
	c++ -std=c++17 -Iinclude -Ibuild src/main.cpp build/parser.cpp build/scanner.cpp -o build/compiler

run: all
	./build/compiler < examples/example.lang

clean:
	rm -rf build