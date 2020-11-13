# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 19:26:39 by fulldemo          #+#    #+#              #
#    Updated: 2020/11/13 10:57:27 by fulldemo         ###   ########.fr        #
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
	@make -s -j -C $(LIBFT)
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFTDIR)libft.a -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

run: all
	 ./$(NAME)
.PHONY:		all clean fclean re run