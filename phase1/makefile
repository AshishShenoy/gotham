BIN=gotham

$(BIN): lex.yy.c y.tab.c
	@gcc -lfl lex.yy.c y.tab.c -o $(BIN)

lex.yy.c: prog.l y.tab.h
	@lex prog.l

y.tab.h: prog.y 
	@yacc -Wno-yacc -d prog.y

y.tab.c: prog.y 
	@yacc -Wno-yacc prog.y

clean:
	rm -f $(BIN) lex.yy.c y.tab.c y.tab.h symbol_table.txt

run: $(BIN) test.go
	@./$(BIN) < test.go
	@expand -t 8 symbol_table.txt > temp.txt
	@cat temp.txt > symbol_table.txt
	@rm temp.txt

dump: prog.l prog.y
	@lex prog.l
	@yacc -Wno-yacc -Wcounterexamples -d prog.y
	@yacc -Wno-yacc -Wcounterexamples prog.y
	@gcc -lfl lex.yy.c y.tab.c
	@./$(BIN)
