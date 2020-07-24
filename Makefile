SRC = main.cpp
OBJS = $(SRC:.cpp=.o)
OUT = program.exe

# Dla windowsa 
# CXX = x86_64-w64-mingw32-g++
CXX = g++
INC_DIR = .
CXXFLAGS = -std=c++17 -O3 -I$(INC_DIR) 
LDFLAGS = -static -static-libgcc
DEPS = $(shell find . -name "*.h")

all: algo

run: algo
	./algo

w64-run: w64-algo
	wineconsole algow64.exe

clean:
	rm -f $(OUT) $(OBJS)
	rm -f *~

algo: $(OBJS) 
	@echo $(DEPS)
	${CXX} ${CXXFLAGS} $< $(LDFLAGS) -o $@ 

w64-algo: $(OBJS)  $(DEPS)
	@echo $(DEPS)
	${CXX} ${CXXFLAGS} $(OBJS) $(LDFLAGS) -o algow64.exe

.PHONY: help
help:
	@echo "        POMOC"
	@echo "algo     - skompiluj na linuxie"
	@echo "run      - Uruchom na linuxie"
	@echo "Before any w64-* action "
	@echo "sudo apt-get install -y mingw-w64 wine64"
	@echo "w64-algo - skompiluj na linuxie "
	@echo "w64-run  - skompiluj na linuxie i uruchom w WINE"
