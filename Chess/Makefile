CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o chessgame.o board.o cell.o move.o player.o piece.o computerplayer.o humanplayer.o king.o queen.o rook.o bishop.o knight.o pawn.o subject.o text.o graphics.o window.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

