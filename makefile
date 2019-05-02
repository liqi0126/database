CC=g++

main: main.o controller.o ui.o basesystem.o database.o table.o whereclause.o

main.o: main.cpp controller.h

controller.o: controller.cpp controller.h ui.h basesystem.h

ui.o: ui.cpp ui.h

basesystem.o: basesystem.cpp basesystem.h database.h

database.o: database.cpp database.h table.h

table.o: table.cpp table.h attr.h whereclause.h

whereclause.o: whereclause.cpp whereclause.h attr.h

clean:
	del *.o main