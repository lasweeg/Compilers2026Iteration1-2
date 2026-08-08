CXX = c++
CXXFLAGS = -std=c++17

HOMEBREW_BISON = /opt/homebrew/opt/bison/bin/bison
HOMEBREW_FLEX = /opt/homebrew/opt/flex/bin/flex
BISON = $(if $(wildcard $(HOMEBREW_BISON)),$(HOMEBREW_BISON),bison)
FLEX = $(if $(wildcard $(HOMEBREW_FLEX)),$(HOMEBREW_FLEX),flex)

UNAME = $(shell uname -s)
MACOS_SDK = $(shell xcrun --show-sdk-path 2>/dev/null)
MACOS_CXX_HEADERS = $(MACOS_SDK)/usr/include/c++/v1

ifeq ($(UNAME),Darwin)
ifneq ($(wildcard $(MACOS_CXX_HEADERS)/string),)
CXXFLAGS += -nostdinc++ -isystem $(MACOS_CXX_HEADERS)
endif
endif

.PHONY: all clean

all: compiler

compiler: main.cpp parser.cpp scanner.cpp ast.hpp visitor.hpp interpreter.hpp print_visitor.hpp
	$(CXX) $(CXXFLAGS) main.cpp parser.cpp scanner.cpp -o compiler

parser.cpp: parser.y
	$(BISON) -d -o parser.cpp parser.y

parser.hpp: parser.cpp

scanner.cpp: scanner.l parser.hpp
	$(FLEX) -o scanner.cpp scanner.l

clean:
	rm -f compiler parser.cpp parser.hpp scanner.cpp stack.hh ast.txt
