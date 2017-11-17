EXEC = ex

$(EXEC): $(EXEC).l 
	flex -o $(EXEC).c $(EXEC).l
	gcc -o $(EXEC) $(EXEC).c 

teste: $(EXEC)
	./$(EXEC) < exemplo2.txt
