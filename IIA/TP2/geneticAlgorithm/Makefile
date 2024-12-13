CC = gcc
CFLAGS = -Wall -g -lm

# Arquivos de origem
SRC = main.c coin_change_ea.c utils.c
OBJ = $(SRC:.c=.o)
EXEC = coin_change

# Regra para compilar o programa
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Regra para compilar os arquivos .c em .o
.c.o:
	$(CC) $(CFLAGS) -c $<

# Limpar arquivos compilados
clean:
	rm -f $(OBJ) $(EXEC)
