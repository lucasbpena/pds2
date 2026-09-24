	CC=g++
	CFLAGS=-std=c++11 -Wall -I./include

	BUILD_DIR=./build
	SRC_DIR=./src

	all: vpl_execution

	${BUILD_DIR}/Ponto.o: ./src/entidades/Ponto.cpp ./include/Ponto.hpp
		${CC} ${CFLAGS} -c ./src/entidades/Ponto.cpp -o ${BUILD_DIR}/Ponto.o

	${BUILD_DIR}/Circulo.o: ./src/entidades/Circulo.cpp ./include/Circulo.hpp ./include/Ponto.hpp
		${CC} ${CFLAGS} -c ./src/entidades/Circulo.cpp -o ${BUILD_DIR}/Circulo.o

	${BUILD_DIR}/main.o: ./src/main.cpp ./include/Ponto.hpp ./include/Circulo.hpp
		${CC} ${CFLAGS} -c ./src/main.cpp -o ${BUILD_DIR}/main.o

	vpl_execution: ${BUILD_DIR}/main.o ${BUILD_DIR}/Ponto.o ${BUILD_DIR}/Circulo.o
		${CC} ${CFLAGS} ${BUILD_DIR}/main.o ${BUILD_DIR}/Ponto.o ${BUILD_DIR}/Circulo.o -o vpl_execution

	clean:
		rm -f ${BUILD_DIR}/*.o vpl_execution
