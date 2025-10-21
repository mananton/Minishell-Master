NAME	=	libft.a
CC		=	@cc
AR		=	@ar rcs
CFLAGS	=	-Wall -Wextra -Werror -MMD -MP -g

BIN_DIR	=	bin/
SRC_DIR	=	src/
INC_DIR	=	inc/
OBJ_DIR	=	obj/
DEP_DIR	=	dep/

SRC 	=	lib/ft_atoi.c \
			lib/ft_bzero.c \
			lib/ft_calloc.c \
			lib/ft_char_to_str.c \
			lib/ft_free.c \
			lib/ft_isalnum.c \
			lib/ft_isalpha.c \
			lib/ft_isascii.c \
			lib/ft_isblank.c \
			lib/ft_isdigit.c \
			lib/ft_islower.c \
			lib/ft_isprint.c \
			lib/ft_isspace.c \
			lib/ft_isstrdigit.c \
			lib/ft_isupper.c \
			lib/ft_itoa.c \
			lib/ft_lstadd_back.c \
			lib/ft_lstadd_front.c \
			lib/ft_lstclear.c \
			lib/ft_lstdelone.c \
			lib/ft_lstiter.c \
			lib/ft_lstlast.c \
			lib/ft_lstmap.c \
			lib/ft_lstnew.c \
			lib/ft_lstsize.c \
			lib/ft_memccpy.c \
			lib/ft_memchr.c \
			lib/ft_memcmp.c \
			lib/ft_memcpy.c \
			lib/ft_memmove.c \
			lib/ft_memset.c \
			lib/ft_putchar_fd.c \
			lib/ft_putendl_fd.c \
			lib/ft_putnbr_fd.c \
			lib/ft_putstr_fd.c \
			lib/ft_split.c \
			lib/ft_strcat_char.c \
			lib/ft_strchr.c \
			lib/ft_strcmp.c \
			lib/ft_strdup.c \
			lib/ft_strichr.c \
			lib/ft_strjoin.c \
			lib/ft_strlcat.c \
			lib/ft_strlcpy.c \
			lib/ft_strlen.c \
			lib/ft_strmapi.c \
			lib/ft_strncmp.c \
			lib/ft_strnstr.c \
			lib/ft_strrchr.c \
			lib/ft_strstr.c \
			lib/ft_strtrim.c \
			lib/ft_substr.c \
			lib/ft_tolower.c \
			lib/ft_toupper.c
SRCS	= $(addprefix $(SRC_DIR), $(SRC))
OBJS	= $(patsubst $(SRC_DIR)%, $(OBJ_DIR)%,$(SRCS:.c=.o))
DEPS	= $(patsubst $(SRC_DIR)%, $(DEP_DIR)%,$(SRCS:.c=.d))

INCS	= -I$(INC_DIR)

RESET	= \033[0m
BOLD	= \033[1m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m


all: $(BIN_DIR)$(NAME)

$(OBJ_DIR) $(DEP_DIR) $(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)$*.d)
	$(CC) $(CFLAGS) ${INCS} -c $< -o $@ -MF $(DEP_DIR)$*.d || { echo "$(RED)Failed to create lib obj/dep$(RESET)"; exit 1; }

$(BIN_DIR)$(NAME): $(OBJS) | $(BIN_DIR)
	$(AR) $@ $(OBJS) || { echo "$(RED)Failed to create lib$(RESET)"; exit 1; }
	@echo "$(BOLD)$(GREEN)Library compiled succesfully$(RESET)"

clean:
	@if [ -d $(OBJ_DIR) ] || [ -d $(DEP_DIR) ]; then \
		echo "$(BOLD)$(YELLOW)Cleaning lib$(RESET)"; \
		rm -rf $(OBJ_DIR) $(DEP_DIR); \
		echo "$(BOLD)$(GREEN)Lib clean$(RESET)"; \
	else \
		echo "$(BOLD)$(BLUE)No objs or deps to clean in lib$(RESET)"; \
	fi

fclean: clean
	@rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all re clean fclean

-include ${DEPS}
