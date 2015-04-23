NAME	= raytracer

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -I include -std=c11 -g -D _BSD_SOURCE

LDFLAGS	= -lmlx -lXext -lX11 -lm

SRC	= src/main.c \
	  src/Vec3.c \
	  src/Vec2.c \
	  src/Mat4x4.c \
	  src/Color.c \
	  src/Utils.c \
	  src/List.c \
	  src/XContext.c \
	  src/Image.c \
	  src/Object.c \
	  src/Sphere.c \
	  src/Intersection.c \
	  src/Ray.c \
	  src/Camera.c \

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
