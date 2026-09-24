CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRCS = main.cpp Jogador.cpp Tabuleiro.cpp Partida.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = jogo

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
