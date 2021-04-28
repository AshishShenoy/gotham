YFLAGS=-Wno-yacc -Wno-other -Wno-conflicts-sr

a.out: lex.yy.c y.tab.c
	@gcc -lfl lex.yy.c y.tab.c

lex.yy.c: prog.l y.tab.h
	@lex prog.l

y.tab.h: prog.y 
	@yacc $(YFLAGS) -d prog.y

y.tab.c: prog.y 
	@yacc $(YFLAGS) prog.y

clean:
	rm -f a.out lex.yy.c y.tab.c y.tab.h icg.txt

run: a.out test.go
	@./a.out < test.go
