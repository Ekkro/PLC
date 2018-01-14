EXEC=galo

$(EXEC): $(EXEC).l $(EXEC).y
	flex -o $(EXEC).c $(EXEC).l
	yacc -d -v $(EXEC).y
	gcc -o $(EXEC) y.tab.c -lm

teste: $(EXEC)
	./$(EXEC) < input.txt

pdf: 
	evince ../VMdocpt.pdf &

vm:
	java -jar ../dist/vm.jar &
