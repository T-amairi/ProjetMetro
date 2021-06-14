CC=gcc
CFLAGS= -Wall 
LDFLAGS = -lm
SRC= $(wildcard *.c)  # on prendre tout les fichier .c et les mettre dans la variable SRC
OBJ= $(SRC:.c=.o) # on change les fichiers .c en fichiers.o
EXEC = main

all: $(EXEC)
%.o: %.c  
	$(CC) $(CFLAGS) -o $@ -c $<   
	 
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@   
	

clean: 
	rm -f $(OBJ) $(EXEC) 	

