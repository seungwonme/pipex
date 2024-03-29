.SUFFIXES : .c .o

NAME    := pipex
CC      := cc
CFLAGS  := -Wall -Werror -Wextra
MEMORY  := -g3 -fsanitize=address
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

SRC     := \
		main.c \
		pipex.c \
		here_doc.c \
		utils.c \
		safe_syscalls.c 
OBJ     := $(addprefix $(SRC_DIR)/, $(SRC:.c=.o))

LIBFT   := ./libft/libft.a

all: $(NAME)
	@echo "$(GREEN)$(NAME) created successfully$(RESET)"

bonus: $(NAME)
	@echo "$(GREEN)Bonus part compiled successfully$(RESET)"

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
	@echo "$(YELLOW)Executable compiled with memory sanitizer$(RESET)"

lldb:
	@$(MAKE) fclean
	@$(MAKE) lldb -C ./libft
	@$(MAKE) all CFLAGS="$(LLDB)"
	@echo "$(YELLOW)Executable compiled to enable LLDB debugging$(RESET)"

.PHONY: all clean fclean re mem lldb bonus
