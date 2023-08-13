.PHONY: all clean fclean

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

#EXECUTAVEIS
NAME = minishell
NAME_A = $(NAME).a

#DIRETORIOS
SRC_DIR = src
OBJ_DIR = .obj
LIBFT = libft/

#ARQUIVOS
LIBFT_A = libft/libft.a
SRCS =	$(SRC_DIR)/data.c\
		$(SRC_DIR)/envp.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/exec.c \
		$(SRC_DIR)/export.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/chdir.c \
		$(SRC_DIR)/util_string.c \
		$(SRC_DIR)/util_envp.c \
		$(SRC_DIR)/util.c \
		$(SRC_DIR)/error.c \
		$(SRC_DIR)/echo.c \
		$(SRC_DIR)/unset.c \

#ARQUIVOS .o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

#MAIN
MAIN = $(SRC_DIR)/main.c
#$(SRC_DIR)/readline.c

#COMANDOS
CC = cc
AR = ar rcs
RM = rm -f
MKDIR = mkdir -p

#FLAGS
FLAGS = -g -Werror -Wextra -Wall -lreadline
OUTPUT = -o

all: $(NAME)

libft_compile:
	@echo $(AMARELO)"Compilando\tlibft     " $(<:src/%=%) $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@make -C $(LIBFT) --silent
	@echo $(VERDE)"Libft compilado     " $(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)

libft_clean:
	@echo $(VERMELHO)"Removendo objetos libft\t" $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@make clean -C $(LIBFT) --silent

libft_fclean:
	@echo $(VERMELHO)"Removendo binario libft"$(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@make fclean -C $(LIBFT) --silent

$(NAME): $(OBJS) libft_compile
	@echo $(VERDE)"Criando executavel minishell" $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(CC) $(MAIN) $(OBJS) $(LIBFT_A) $(FLAGS) $(OUTPUT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(OBJ_DIR)
	@echo $(AMARELO)"Compilando     " $(<:src/%=%) $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(CC) -c $< -o $@

clean:	libft_clean
	@echo $(VERMELHO)"Removendo objetos\t" $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(RM) $(OBJ_DIR)/*.o

fclean: clean libft_fclean
	@echo $(VERMELHO)"Removendo executavel philo"$(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)

re: fclean all

git:
	git add *
	git commit -m .
	git push
