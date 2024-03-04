# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 15:09:12 by mpitot            #+#    #+#              #
#    Updated: 2024/03/04 19:43:09 by mpitot           ###   ########.fr        #
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

FLAGS	=	-Wall -Wextra -Werror -g3

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

NUM_SRCS := $(words $(SRCS) + 1)
COMPILED_SRCS := 0

define print_progress
	@echo "$(YELLOW)Compiling $(WHITE)[$(BLUE)$1$(WHITE)]...$(DEFAULT)\r"
endef

define update_progress
	$(eval COMPILED_SRCS := $(shell echo $$(($(COMPILED_SRCS) + 1))))
	$(eval PROGRESS := $(shell echo $$((($(COMPILED_SRCS) * 100) / $(NUM_SRCS)))))
	@printf ${UP}${CUT}
	@if [ $(PROGRESS) -eq 100 ]; then \
		echo "$(WHITE)<$(GREEN)$(PROGRESS)%$(WHITE)> $(WHITE)[$(BLUE)$1$(WHITE)] $(YELLOW)compiled.$(DEFAULT)\r"; \
	else \
		if [ $(PROGRESS) -lt 10 ]; then \
			echo "$(WHITE)<  $(GREEN)$(PROGRESS)%$(WHITE)> $(WHITE)[$(BLUE)$1$(WHITE)] $(YELLOW)compiled.$(DEFAULT)\r"; \
		else \
			echo "$(WHITE)< $(GREEN)$(PROGRESS)%$(WHITE)> $(WHITE)[$(BLUE)$1$(WHITE)] $(YELLOW)compiled.$(DEFAULT)\r"; \
		fi \
	fi
endef

define progress_bar
	$(eval COMPILED_SRCS := $(shell echo $$(($(COMPILED_SRCS) + 1))))
	$(eval PROGRESS := $(shell echo $$((($(COMPILED_SRCS) * 60) / $(NUM_SRCS)))))
	@echo -n "$(WHITE)[$(GREEN)"
	@for i in $$(seq 1 $(PROGRESS)); do \
		echo -n "#"; \
	done
	echo "$(WHITE)"
	@for i in $$(seq 1 $$(($(NUM_SRCS) - $(PROGRESS)))); do \
		echo -n "_"; \
	done
	@echo -n "]$(DEFAULT)"
endef

#-L/var/lib/flatpak/runtime/org.freedesktop.Sdk/x86_64/23.08/2f00425aee448b08810bf671103aef1140d844be0cc88bac7a8c6b6145d16455/files/lib/x86_64-linux-gnu

all		:	${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c includes/philo.h
	@${CC} ${FLAGS} -I${HEAD} -c $< -o $@
	@printf ${UP}${CUT}
	@$(call progress_bar)

${NAME}	:	${OBJ_D} ${OBJS} Makefile includes/philo.h
	@echo "$(YELLOW)Compiling $(WHITE)[$(BLUE)$(NAME)$(WHITE)]...$(DEFAULT)"
	@${CC} ${FLAGS} -pthread -lpthread -I${HEAD} -o ${NAME} ${OBJS}
	@$(eval CHANGED=1)
	@printf ${UP}${CUT}
	@echo "$(WHITE)<$(GREEN)100%$(WHITE)> [$(CYAN)$(NAME)$(WHITE)] $(GREEN)compiled.$(DEFAULT)"

${OBJ_D}:
	@mkdir -p ${OBJ_D}

clean	:
	@echo "Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"

fclean	:
	@echo "FCleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"
	@rm -f ${NAME}
	@echo "$(WHITE)[$(RED)$(NAME)$(WHITE)] $(RED)deleted.$(DEFAULT)"

re		:	fclean .internal_separate all

.PHONY	:	all clean fclean re

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for $(WHITE)[$(CYAN)$(NAME)$(WHITE)].$(DEFAULT)"; \
	fi

.internal_separate	:
	@echo "$(WHITE)------------------------------------------------------------$(DEFAULT)"
