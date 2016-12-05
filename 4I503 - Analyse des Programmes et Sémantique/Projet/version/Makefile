CC = g++
CFLAGS = -Wall
EXEC_NAME = aps_launcher
INCLUDES =
LIBS =
OBJ_FILES =

all : aps

clean :
	rm $(EXEC_NAME) $(OBJ_FILES) analyzer.tab.c analyzer.tab.h lex.yy.c

aps : bison flex
	g++ -std=c++11 analyzer.tab.c lex.yy.c -lfl -o aps_launcher

bison: 
	bison -d analyzer.y

flex: analyzer.tab.c
	flex analyzer.l

#$(EXEC_NAME) : $(OBJ_FILES) 
#$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

 
 	
