CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
TARGET   = meharaben.exe

SRCS = src/main.cpp \
       src/game.cpp \
       src/mechanics.cpp \
       src/players.cpp \
       src/timer.cpp \
       src/display.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	del /Q src\*.o $(TARGET) 2>nul || true

.PHONY: all clean
