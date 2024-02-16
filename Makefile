# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 14:43:50 by jhoratiu          #+#    #+#              #
#    Updated: 2024/02/14 16:25:04 by jhoratiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Imlx -g3
AR = ar rcs
RM = rm -f
FILES = ./main/animation.c \
./main/hooks.c \
./main/init.c \
./main/map.c \
./main/so_long.c \
./main/utils.c \
./get_next_line/get_next_line.c \
./get_next_line/get_next_line_utils.c \
./sprintf/printf_main.c \
./sprintf/printf_verifs.c \
./sprintf/printf_verifs2.c \

IMGS = sprites/attacks/projectile1.png \
sprites/attacks/projectile2.png \
sprites/character/death/death0.png \
sprites/character/death/death1.png \
sprites/character/death/death2.png \
sprites/character/death/death3.png \
sprites/character/death/death4.png \
sprites/character/death/death5.png \
sprites/character/death/death6.png \
sprites/character/passive/pass0.png \
sprites/character/passive/pass1.png \
sprites/character/passive/pass2.png \
sprites/character/passive/pass3.png \
sprites/character/run/run0.png \
sprites/character/run/run1.png \
sprites/character/run/run2.png \
sprites/character/run/run3.png \
sprites/character/run/run4.png \
sprites/collectible/fulmine0.png \
sprites/collectible/fulmine1.png \
sprites/enemies/enemy1/init0.png \
sprites/enemies/enemy1/init1.png \
sprites/enemies/enemy1/init2.png \
sprites/enemies/enemy1/init3.png \
sprites/enemies/enemy1.png \
sprites/map/floor_industrial.png \
sprites/map/map_lava.png \
sprites/map/map_wall.png \
sprites/map/map.png \
sprites/map/wall_industrial.png \
sprites/npc/npc1.png \

OBJS=$(FILES:.c=.o)
SPRITES=$(IMGS:.png=.xpm)

all: $(NAME)

minilibx-linux/libmlx.a:
	make -C minilibx-linux

$(NAME): $(OBJS) $(SPRITES) minilibx-linux/libmlx.a
	$(CC) $(OBJS) -Lminilibx-linux -lmlx -lX11 -lXext -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.xpm: %.png
	convert $< $@

clean:
	 $(RM) $(NAME) $(OBJS) $(SPRITES)

fclean: clean
	$(RM) $(NAME)

re: clean all

bonus: $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS)

.PHONY: all clean fclean re bonus