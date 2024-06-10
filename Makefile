# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 08:58:56 by lgosselk          #+#    #+#              #
#    Updated: 2024/03/14 11:09:36 by lgosselk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

GCC		=	gcc
RM		=	rm -rf
HEADER	=	-I includes
FLAGS	= 	-Wall -Wextra -Werror

DEFAULT = \033[0m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m

SRCS_DIR	=	src/
OBJS_DIR	=	objs/
UTILS_DIR	=	utils/
ERRORS_DIR	=	errors/
ROUTINE_DIR	=	routine/

F_ERRORS	=	errors
F_UTILS		= 	utils utils_2
F_ROUTINE	=	actions init routine

FILES		=	$(addprefix $(UTILS_DIR), $(F_UTILS)) \
				$(addprefix $(ERRORS_DIR), $(F_ERRORS)) \
				$(addprefix $(ROUTINE_DIR), $(F_ROUTINE)) \

SRCS		=	src/main.c \
				$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES))) \
			
OBJS		=	objs/main.o \
				$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES))) \

all:		$(OBJS_DIR) $(NAME)

$(NAME):		$(OBJS)
				@$(GCC) $(FLAGS) $(OBJS) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@echo "$(YELLOW)$< en compilation!$(DEFAULT)"
				@$(GCC) $(FLAGS) $(HEADER) -o $@ -c $<

$(OBJS_DIR):
				@mkdir -p $(OBJS_DIR)
				@mkdir -p $(OBJS_DIR)$(UTILS_DIR)
				@mkdir -p $(OBJS_DIR)$(ERRORS_DIR)
				@mkdir -p $(OBJS_DIR)$(ROUTINE_DIR)

clean:
				@$(RM) $(OBJS_DIR)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:		clean
				@$(RM) $(NAME)
				@echo "$(RED)all deleted!$(DEFAULT)"

re:			fclean all

.PHONY:		all clean fclean re