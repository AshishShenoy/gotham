a.out: lex.yy.c y.tab.c
	@gcc -lfl lex.yy.c y.tab.c

lex.yy.c: prog.l y.tab.h
	@lex prog.l

y.tab.h: prog.y 
	@yacc -Wno-yacc -d prog.y

y.tab.c: prog.y 
	@yacc -Wno-yacc prog.y

clean:
	rm -f a.out lex.yy.c y.tab.c y.tab.h symbol_table.txt

run: a.out test.go
	@./a.out < test.go
	@expand -t 8 symbol_table.txt > temp.txt
	@cat temp.txt > symbol_table.txt
	@rm temp.txt

dump: prog.l prog.y
	@lex prog.l
	@yacc -Wno-yacc -Wcounterexamples -d prog.y
	@yacc -Wno-yacc -Wcounterexamples prog.y
	@gcc -lfl lex.yy.c y.tab.c
	@./a.out
