NAME		= cub3D

SRC_DIR		= src
OBJ_DIR		= objs
INC_DIR		= includes
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

SRC_FILES	=	main.c \
				game/game.c \
				game/controls.c \
				game/init_mlx.c \
				game/key_hook.c \
				game/initialize.c \
				render/render.c \
				render/textures.c \
				render/ray.c \
				render/render_utils.c \
				game/minimap.c \
				game/minimap_utils.c \
				game/minimap_border.c \
				utils/error.c \
				parser/parse_map_utils.c parser/parse_map.c parser/parse_textures.c \
				parser/parse_colors.c parser/parser.c parser/read_lines.c \
				parser/parse_colors_utils.c parser/validate.c \
				utils/common_utils.c utils/log_mesg.c utils/cleanup.c
SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
LDLIBS		= $(LIBFT) $(MLX) -lXext -lX11 -lm

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR) CC="cc -Wno-strict-prototypes -Wno-return-type -Wno-parentheses -Wno-pointer-sign"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LDLIBS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
