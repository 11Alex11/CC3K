CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = cc3k
OBJECTS = main.o chamberfloor.o doorway.o dragon.o emptywall.o enemy.o entity.o floor.o game.o goblin.o hallway.o horizontalwall.o merchant.o phoenix.o player.o textdisplay.o treasure.o troll.o vampire.o vector.o verticalwall.o werewolf.o dragonhoard.o poisonhealth.o restorehealth.o boostattack.o boostdefence.o woundattack.o wounddefence.o utilities.o stairs.o potion.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
