# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 14:43:50 by jhoratiu          #+#    #+#              #
#    Updated: 2024/03/08 16:38:16 by jhoratiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC 				= cc
CFLAGS 			= -Wall -Wextra -Imlx -g3
RM 				= rm -f
EXTF 			= .c

# FILES
MAINPRE 		= ./main/
GNLPRE 			= ./get_next_line/
SPFPRE 			= ./sprintf/

MAINFILES 		= animation \
				character \
				collectible \
				enemy \
				exit \
				free \
				graphic \
				hooks \
				init \
				map \
				so_long \
				utils \

GNLFILES 		= get_next_line \
				get_next_line_utils \

SPFFILES 		= printf_main \
				printf_verifs \
				printf_verifs2 \

SRCS 			= $(addsuffix ${EXTF}, \
					$(addprefix $(MAINPRE), $(MAINFILES)) \
					$(addprefix $(GNLPRE), $(GNLFILES)) \
					$(addprefix $(SPFPRE), $(SPFFILES)) \
				)

OBJS=$(SRCS:.c=.o)

# SPRITES
EXTPIC 			= .png
SPRITEPRE 		= ./sprites/

ATKPRE 			= $(SPRITEPRE)attacks/
BANPRE 			= $(SPRITEPRE)banner/
CHARPRE 		= $(SPRITEPRE)character/
COLLPRE 		= $(SPRITEPRE)collectible/
ENEMPRE 		= $(SPRITEPRE)enemies/
EXITPRE 		= $(SPRITEPRE)exit/
MAPPRE 			= $(SPRITEPRE)map/
NPCPRE 			= $(SPRITEPRE)npc/

ATKFILES = 		projectile1 \
				projectile2 \

BANFILES =		banner0 \
				banner1 \
				banner2 \
				banner3 \

CHARFILES = 	death/death0 \
				death/death1 \
				death/death2 \
				death/death3 \
				death/death4 \
				death/death5 \
				death/death6 \
				death/death7 \
				passive/pass0 \
				passive/pass1 \
				passive/pass2 \
				passive/pass3 \
				run/run0 \
				run/run1 \
				run/run2 \
				run/run3 \
				run/run4 \

COLLFILES = 	cube0 \
				cube1 \
				cube2 \
				cube3 \

ENEMFILES = 	enemy1/init0 \
				enemy1/init1 \
				enemy1/init2 \
				enemy1/init3 \
				enemy_atk/attack0 \
				enemy_atk/attack1 \
				enemy_atk/attack2 \
				enemy1 \

EXITFILES = 	portal0 \
				portal1 \
				portal2 \
				portal3 \

MAPFILES =		floor_industrial \
				map_lava \
				map_wall \
				map \
				wall_industrial \

NPCFILES =		npc1 \

IMGS =			$(addsuffix ${EXTPIC}, \
					$(addprefix $(ATKPRE), $(ATKFILES)) \
					$(addprefix $(BANPRE), $(BANFILES)) \
					$(addprefix $(CHARPRE), $(CHARFILES)) \
					$(addprefix $(COLLPRE), $(COLLFILES)) \
					$(addprefix $(ENEMPRE), $(ENEMFILES)) \
					$(addprefix $(EXITPRE), $(EXITFILES)) \
					$(addprefix $(MAPPRE), $(MAPFILES)) \
					$(addprefix $(NPCPRE), $(NPCFILES)) \
				)

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

# bonus: $(OBJS) $(OBJS_BONUS)
# 	$(AR) $(NAME) $(OBJS)

.PHONY: all clean fclean re bonus