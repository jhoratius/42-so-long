# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 14:43:50 by jhoratiu          #+#    #+#              #
#    Updated: 2024/04/05 13:10:13 by jhoratiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -Imlx -g3
RM 				= rm -f
EXTF 			= .c

# FILES
MAINPRE 		= ./main/
GNLPRE 			= ./get_next_line/
SPFPRE 			= ./sprintf/
PFPRE 			= ./printf/

MAINFILES 		=	character \
				collectible \
				display \
				draws \
				exit \
				free \
				graphic \
				hooks \
				init \
				map_parsing \
				map \
				pathfinding \
				print_steps \
				so_long \
				utils \
				utils2 \

GNLFILES 		= get_next_line \
				get_next_line_utils \

SPFFILES 		= sprintf_main \
				sprintf_verifs \
				sprintf_verifs2 \

PFFILES 		= printf_main \
				printf_verifs \
				printf_verifs2 \
				

SRCS 			= $(addsuffix ${EXTF}, \
					$(addprefix $(MAINPRE), $(MAINFILES)) \
					$(addprefix $(GNLPRE), $(GNLFILES)) \
					$(addprefix $(SPFPRE), $(SPFFILES)) \
					$(addprefix $(PFPRE), $(PFFILES)) \
				)

OBJS=$(SRCS:.c=.o)

# SPRITES
EXTPIC 			= .png
SPRITEPRE 		= ./sprites/

CHARPRE 		= $(SPRITEPRE)character/
COLLPRE 		= $(SPRITEPRE)collectible/
EXITPRE 		= $(SPRITEPRE)exit/
MAPPRE 			= $(SPRITEPRE)map/

CHARFILES = 	robot \

COLLFILES = 	cube \

EXITFILES = 	portal \

MAPFILES =		floor_industrial \
				wall_industrial \

IMGS =			$(addsuffix ${EXTPIC}, \
					$(addprefix $(CHARPRE), $(CHARFILES)) \
					$(addprefix $(COLLPRE), $(COLLFILES)) \
					$(addprefix $(EXITPRE), $(EXITFILES)) \
					$(addprefix $(MAPPRE), $(MAPFILES)) \
				)

SPRITES=$(IMGS:.png=.xpm)

all: $(NAME)

minilibx-linux/libmlx.a:
	make -C minilibx-linux

$(NAME): $(OBJS) $(SPRITES) minilibx-linux/libmlx.a
	$(CC) $(OBJS) -Lminilibx-linux -lmlx -lX11 -lXext -o $(NAME) -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.xpm: %.png
	convert $< $@

clean:
	 $(RM) $(NAME) $(OBJS) $(SPRITES)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus