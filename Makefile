# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 19:26:39 by fulldemo          #+#    #+#              #
#    Updated: 2020/06/29 16:44:47 by fulldemo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCDIR	=	./src
INCDIR	=	./includes
OBJDIR	=	./obj
LIBFTDIR = ./libft/

SRC		=	main.c \
			minishell.c \
			utils.c \
			get_next_line.c \
			get_commands.c \
			ft_echo.c \
			ft_doublestrdup.c \
			ft_env.c \
			ft_export.c \
			ft_unset.c \
			ft_cd.c \
			ft_pwd.c \
			ft_exit.c \
			dolar.c \
			parse_redirection.c \
			fd_redirections.c \
			bin_path.c \


OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)
	cd libft ; make;
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFTDIR)libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	cd libft ; make fclean;

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	 ./$(NAME)
.PHONY:		all clean fclean re run