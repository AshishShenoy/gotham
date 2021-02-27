a.out: lex.yy.c y.tab.c
	@gcc -lfl lex.yy.c y.tab.c

lex.yy.c: prog.l y.tab.h
	@lex prog.l

y.tab.h: prog.y 
	@yacc -d prog.y

y.tab.c: prog.y 
	@yacc prog.y

clean:
	rm -f a.out lex.yy.c y.tab.c y.tab.h

run: a.out test
	@./a.out < test.go