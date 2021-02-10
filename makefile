a.out: lex.yy.c test.go
	@gcc lex.yy.c -lfl

lex.yy.c: prog.l
	@lex prog.l

clean:
	rm -f a.out lex.yy.c y.tab.c output.txt
