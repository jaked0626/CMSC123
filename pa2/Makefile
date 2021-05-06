CC      = clang
CFLAGS  = -g -std=c99 -Wall
LD      = $(CC)
LDFLAGS = -lm
VALGRIND = 

EXE  = test_reduce
OBJS = game.o util.o double_table.o

all :	$(EXE)

test_reduce :	test_reduce.c reduce_game.c $(OBJS)
	$(CC) $(CFLAGS) test_reduce.c reduce_game.c $(OBJS) -o $@

run_test_reduce:	test_reduce
	$(VALGRIND) ./test_reduce data

clean:
	rm -f *.o *~
	rm -rf *.dSYM
	rm -f $(EXE)

