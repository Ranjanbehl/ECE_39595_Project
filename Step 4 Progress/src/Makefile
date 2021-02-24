SRC = main.cpp Action.cpp Creature.cpp CreatureAction.cpp Displayable.cpp Dungeon.cpp Items.cpp ItemAction.cpp Structure.cpp XMLHandler.cpp ObjectDisplayGrid.cpp GridChar.cpp Player.cpp Monster.cpp Scroll.cpp Armor.cpp Sword.cpp KeyboardListener.cpp
#HDR= //No longer needed
OBJ = $(patsubst %.c,%.o,$(SRC))
CC = g++
FLAGS = -std=c++11 -g -pthread -O3#-Wall #-Wshadow -Wvla -Werror -pedantic
INCLUDES = -I/usr/local/Cellar/xerces-c/3.2.3/include/ -L/usr/local/Cellar/xerces-c/3.2.3/lib/  -I/usr/local/Cellar/ncurses/6.2/include/ -L/usr/local/Cellar/ncurses/6.2/lib/ 
SUFFIX = -lxerces-c -lncurses
EXECTUABLE = XMLHandler

$(EXECTUABLE): $(SRC) $(HDR)
	$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(SUFFIX)

#prog: $(OBJ) $(HDR)
	#g++ -o $@ $^

#%.o: %.c $(HDR)
	#g++ -g -Wall -Werror $(INCLUDES) -o $@ -c $<

.PHONY: debug clean badScroll.xml death.xml dropPack.xml dungeon.xml hallucinate.xml testDrawing.xml wear.xml

clean: $(EXECTUABLE)
	rm -rf *.o $<
debug: $(EXECTUABLE)
	$(CC) -o $@ $(SRC_C) $(TEST_C) $(FLAGS) -DDEBUG

badScroll.xml : $(EXECTUABLE) 
	./$(EXECTUABLE) badScroll.xml

death.xml : $(EXECTUABLE) 
	./$(EXECTUABLE) death.xml

dropPack.xml : $(EXECTUABLE)
	./$(EXECTUABLE) dropPack.xml

dungeon.xml : $(EXECTUABLE)
	./$(EXECTUABLE) dungeon.xml

hallucinate.xml : $(EXECTUABLE)
	./$(EXECTUABLE) hallucinate.xml

testDrawing.xml : $(EXECTUABLE)
	./$(EXECTUABLE) testDrawing.xml

wear.xml : $(EXECTUABLE)
	./$(EXECTUABLE) wear.xml
