.SUFFIXES : .c .o

NAME    := pipex
CC      := cc
CFLAGS  := -Wall -Werror -Wextra
MEMORT  := -fsanitize=address
LLDB    := -g

BLACK   := \033[30m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE    := \033[34m
MAGENTA := \033[35m
CYAN    := \033[36m
WHITE   := \033[37m
RESET   := \033[0m

INCLUDE := -I./inc -I./libft/inc
SRC_DIR := ./src

SRC    := \
		main.c \
		pipex.c \
		utils.c \
		heredoc.c
OBJ    := $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

LIBFT  := ./libft/libft.a

all: $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	@echo "$(WHITE)Creating $@$(RESET)"

$(LIBFT):
	@$(MAKE) bonus -C ./libft
	@echo "$(GREEN)libft compiled successfully$(RESET)"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(CYAN)Compiled:$(RESET) $< -> $@"

clean:
	@$(MAKE) clean -C ./libft
	@rm -f $(OBJ)
	@echo "$(BLUE)Cleaned up object files$(RESET)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@echo "$(BLUE)Cleaned up executable and library$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

mem:
	@$(MAKE) fclean
	@$(MAKE) mem -C ./libft
	@$(MAKE) all CFLAGS="$(MEMORY)"

lldb:
	@$(MAKE) fclean
	@$(MAKE) lldb -C ./libft
	@$(MAKE) all CFLAGS="$(LLDB)"

.PHONY: all clean fclean re mem lldb
