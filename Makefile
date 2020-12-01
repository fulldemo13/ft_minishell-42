# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 19:26:39 by fulldemo          #+#    #+#              #
#    Updated: 2020/12/01 10:13:13 by fulldemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCDIR	=	./src
INCDIR	=	./includes
OBJDIR	=	./obj
LIBFT 	= libft
LIBFTDIR = ./libft/

SRC		=	main.c \
			minishell.c \
			syntax_errors.c \
			divisor.c \
			dolar.c \
			utils.c \
			get_next_line.c \
			ft_doublestrdup.c \
			ft_exit.c \
			bin_path.c \
			ft_binpath.c \
			ft_cd.c \
			ft_pwd.c \
			ft_env.c \
			ft_export.c \
			ft_unset.c \
			ft_echo.c 

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)
	#cd libft ; make;
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFTDIR)libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	#cd libft ; make clean;

fclean: clean
	rm -f $(NAME)
	#cd libft ; make fclean;

re: fclean all

run: all
	 ./$(NAME)
.PHONY:		all clean fclean re run obj 