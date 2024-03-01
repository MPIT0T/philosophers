# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 15:09:12 by mpitot            #+#    #+#              #
#    Updated: 2024/03/01 20:27:25 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c				\
			utils.c				\
			init.c				\
			print_info.c		\
			time.c				\
			routine_odd.c		\
			routine_pair.c		\
			routine_utils.c		\
			fork_operations.c	\
			free.c

OBJS	=	$(SRCS:%.c=${OBJ_D}%.o)

SRC_D	=	srcs/

OBJ_D	=	.objs/

HEAD	=	includes/

NAME	=	philo

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror #-fsanitize=address -g3

RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
MAGENTA	=	\033[1;35m
CYAN	=	\033[1;36m
WHITE	=	\033[1;37m
DEFAULT	=	\033[0m
UP		=	"\033[A"
CUT		=	"\033[K"

CHANGED	=	0

NUM_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

define print_progress
	@echo "$(YELLOW)Compiling $(WHITE)[$(BLUE)$1$(WHITE)]...$(DEFAULT)\r"
endef

define update_progress
	$(eval COMPILED_SRCS := $(shell echo $$(($(COMPILED_SRCS) + 1))))
	$(eval PROGRESS := $(shell echo $$((($(COMPILED_SRCS) * 100) / $(NUM_SRCS)))))
	@printf ${UP}${CUT}
	@if [ $(PROGRESS) -eq 100 ]; then \
		echo "$(WHITE)<$(GREEN)$(PROGRESS)%$(WHITE)> $(YELLOW)Compiled $(WHITE)[$(BLUE)$1$(WHITE)]$(DEFAULT)\r"; \
	else \
		echo "$(WHITE) <$(GREEN)$(PROGRESS)%$(WHITE)> $(YELLOW)Compiled $(WHITE)[$(BLUE)$1$(WHITE)]$(DEFAULT)\r"; \
	fi
endef

all		:	${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c includes/philo.h
	@$(call print_progress,$<)
	@${CC} ${FLAGS} -I${HEAD} -c $< -o $@
	@$(call update_progress,$<)

${NAME}	:	${OBJ_D} ${OBJS} Makefile includes/philo.h
	@echo ""
	@echo "$(YELLOW)Compiling $(WHITE)[$(BLUE)$(NAME)$(WHITE)]...$(DEFAULT)"
	@${CC} ${FLAGS} -lpthread -I${HEAD} -o ${NAME} ${OBJS}
	@$(eval CHANGED=1)
	@printf ${UP}${CUT}
	@echo "$(WHITE)[$(CYAN)$(NAME)$(WHITE)] $(GREEN)compiled.$(DEFAULT)"
	@echo ""

${OBJ_D}:
	@mkdir -p ${OBJ_D}

clean	:
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"

fclean	:	clean
	@rm -f ${NAME}
	@echo "$(WHITE)[$(RED)$(NAME)$(WHITE)] $(RED)deleted.$(DEFAULT)"

re		:	fclean all

.PHONY	:	all clean fclean re

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for $(WHITE)[$(BLUE)$(NAME)$(WHITE)].$(DEFAULT)"; \
	fi
