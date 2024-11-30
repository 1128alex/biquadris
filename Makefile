CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla
OBJECTS = main.o board.o textRender.o coord.o game.o grid.o controller.o block.o cell.o level.o sequence.o grahpicRender.o window.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
