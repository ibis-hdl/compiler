CC=cc
# CFLAGS=-gx -DBASE_REPRESENTATION
CFLAGS=-gx 
LDFLAGS=-ll

YACC=yacc
YFLAGS=-Nl1200 -d -v -t

LEX=lex

OBJS=y.tab.o lex.yy.o main.o

all: fparse

fparse: $(OBJS)
	$(CC) -o fparse $(CFLAGS) $(OBJS) $(LDFLAGS)

y.tab.o: y.tab.c y.tab.h
	$(CC) -c $(CFLAGS) y.tab.c

y.tab.c y.tab.h: vhdl.yacc
	$(YACC) $(YFLAGS) vhdl.yacc

lex.yy.o: lex.yy.c y.tab.h
	$(CC) -c $(CFLAGS) lex.yy.c

lex.yy.c: vhdl.lex
	$(LEX) vhdl.lex

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(OBJS) core y.* lex.yy.? fparse

