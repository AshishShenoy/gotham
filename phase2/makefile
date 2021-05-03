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
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt

test_for : a.out tests/for_loop.go
	@./a.out < tests/for_loop.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt


test_if_else : a.out tests/if_else_statements.go
	@./a.out < tests/if_else_statements.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt


test_if_else_if : a.out tests/if_else_if_statements.go
	@./a.out < tests/if_else_if_statements.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt

test_nested_if : a.out tests/nested_if.go
	@./a.out < tests/nested_if.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt


test_nested_loop : a.out tests/nested_loops.go
	@./a.out < tests/nested_loops.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt


test_optimisation : a.out tests/optimisation.go
	@./a.out < tests/optimisation.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt


test_nested_conditional : a.out tests/nested_conditionals_loops.go
	@./a.out < tests/nested_conditionals_loops.go
	@expand -t 8 icg.txt > temp.txt
	@cat temp.txt > icg.txt
	@rm temp.txt
	@python icg_optimize.py icg.txt