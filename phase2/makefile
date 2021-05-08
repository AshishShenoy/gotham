YFLAGS=-Wno-yacc -Wno-other -Wno-conflicts-sr
BIN=gotham

$(BIN): lex.yy.c y.tab.c
	@gcc -lfl lex.yy.c y.tab.c -o $(BIN)

lex.yy.c: prog.l y.tab.h
	@lex prog.l

y.tab.h: prog.y 
	@yacc $(YFLAGS) -d prog.y

y.tab.c: prog.y 
	@yacc $(YFLAGS) prog.y

clean:
	rm -f $(BIN) lex.yy.c y.tab.c y.tab.h icg.txt optimized_icg.txt optimization_steps.txt

run: $(BIN) test.go
	@./$(BIN) < test.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python3 icg_optimize.py

test_for : $(BIN) tests/for.go
	@./$(BIN) < tests/for.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt

test_if_else : $(BIN) tests/if_else.go
	@./$(BIN) < tests/if_else.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt

test_if_else_if : $(BIN) tests/if_else_if.go
	@./$(BIN) < tests/if_else_if.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt

test_nested_if : $(BIN) tests/nested_if.go
	@./$(BIN) < tests/nested_if.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt


test_nested_for : $(BIN) tests/nested_for.go
	@./$(BIN) < tests/nested_for.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt

test_optimisation : $(BIN) tests/optimisation.go
	@./$(BIN) < tests/optimisation.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt

test_nested_for_if : $(BIN) tests/nested_for_if.go
	@./$(BIN) < tests/nested_for_if.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt

test: test_if_else test_if_else_if test_nested_if test_for test_nested_for test_nested_for_if test_optimisation
