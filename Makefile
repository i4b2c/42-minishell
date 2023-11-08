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
SRCS =	$(SRC_DIR)/chdir/chdir.c\
		$(SRC_DIR)/data/data.c\
		$(SRC_DIR)/echo/echo.c\
		$(SRC_DIR)/envp/envp.c\
		$(SRC_DIR)/envp/util.c\
		$(SRC_DIR)/error/error.c\
		$(SRC_DIR)/exec/error.c\
		$(SRC_DIR)/exec/exec.c\
		$(SRC_DIR)/exec/util.c\
		$(SRC_DIR)/exec/util2.c\
		$(SRC_DIR)/exit/exit.c\
		$(SRC_DIR)/export/export.c\
		$(SRC_DIR)/free/free.c\
		$(SRC_DIR)/input/input.c\
		$(SRC_DIR)/input/util.c\
		$(SRC_DIR)/input/util2.c\
		$(SRC_DIR)/path/path.c\
		$(SRC_DIR)/redirect/redi.c\
		$(SRC_DIR)/signal/signal.c\
		$(SRC_DIR)/tokens/remove.c\
		$(SRC_DIR)/tokens/tokens.c\
		$(SRC_DIR)/tokens/util.c\
		$(SRC_DIR)/tokens/util2.c\
		$(SRC_DIR)/tokens/util3.c\
		$(SRC_DIR)/unset/unset.c\
		$(SRC_DIR)/utils/check.c\
		$(SRC_DIR)/utils/util_len.c\
		$(SRC_DIR)/utils/util_str.c\
		$(SRC_DIR)/utils/util.c\


#ARQUIVOS .o
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))


#MAIN
MAIN = $(SRC_DIR)/main.c

#COMANDOS
CC = cc
AR = ar rcs
RM = rm -f
MKDIR = mkdir -p

#FLAGS
FLAGS = -g -Werror -Wextra -Wall
OUTPUT = -o

all: $(NAME)

libft_compile:
	@echo $(AMARELO)"Compilando\t   libft     " $(<:src/%=%) $(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@make -C $(LIBFT) --silent
	@echo $(VERDE)"Libft compilado     " $(BRANCO) "\t\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)

libft_clean:
	@echo $(VERMELHO)"Removendo objetos libft\t" $(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@make clean -C $(LIBFT) --silent

libft_fclean:
	@echo $(VERMELHO)"Removendo binario libft"$(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@make fclean -C $(LIBFT) --silent

$(NAME): $(OBJS) libft_compile
	@echo $(VERDE)"Criando executavel minishell" $(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(CC) $(MAIN) $(OBJS) $(LIBFT_A) $(FLAGS) -lreadline $(OUTPUT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(dir $@)
	@echo $(AMARELO)"Compilando        " $(<:$(SRC_DIR)/%=%) $(BRANCO) "\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(CC) $(FLAGS) -c $< -o $@


clean:	libft_clean
	@echo $(VERMELHO)"Removendo objetos\t" $(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(RM) $(OBJ_DIR)/*.o

fclean: clean libft_fclean
	@echo $(VERMELHO)"Removendo executavel minishell"$(BRANCO) "\t\t[" $(VERDE)"✔"$(BRANCO) "]" $(RESETAR)
	@$(RM) $(NAME)
	@$(RM) -rf $(OBJ_DIR)

re: fclean all

git:
	git add *
	git commit -m .
	git push
