NAME = minishell
SRC = src/minishell.c \

#CORES
RESETAR		=		"\033[0m"
BRANCO		=		"\033[1;37m"
PRETO		=		"\033[30m"
VERMELHO	=		"\033[31m"
VERDE		=		"\033[32m"
AMARELO		=		"\033[33m"
AZUL		=		"\033[34m"
ROXO		=		"\033[35m"
CIANO		=		"\033[36m"
CINZA		=		"\033[37m"

#CORES BACKGROUND
BRANCO_BACK		=		"\033[7m"
PRETO_BACK		=		"\033[40m"
VERMELHO_BACK	=		"\033[41m"
VERDE_BACK		=		"\033[42m"
AMARELO_BACK	=		"\033[43m"
AZUL_BACK		=		"\033[44m"
ROXO_BACK		=		"\033[45m"
CIANO_BACK		=		"\033[46m"
CINZA_BACK		=		"\033[47m"

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -lreadline
AR = ar rcs
EXTRA = minishell a.out
LIBFT = libft/libft.a
MAIN = src/main.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
		@echo $(VERDE)"Compiling libft..." $(RESETAR)
		@make --silent -C libft/
		@$(CC) $(MAIN) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

clean:
		@$(RM) $(OBJ)
		@$(RM)

fclean: clean
		@$(RM) $(NAME)
		@make --silent fclean -C libft/
extra: fclean
	@$(RM) $(EXTRA)

re: extra all

ez:
		@$(CC) $(MAIN) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

git:
	git add *
	git commit -m .
	git push

