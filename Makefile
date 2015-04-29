NAME	= raytracer

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -I include -std=c11 -O2 -I /usr/local/include/

LDFLAGS	= -lmlx -lXext -lX11 -lm -lpthread

SRC	= src/Camera.c \
	  src/Color.c \
	  src/DirectionalLight.c \
	  src/Image.c \
	  src/Instance.c \
	  src/Integrator.c \
	  src/Intersection.c \
	  src/LambertMaterial.c \
	  src/Light.c \
	  src/List.c \
	  src/main.c \
	  src/Mat4x4.c \
	  src/Material.c \
	  src/Mesh.c \
	  src/Object.c \
	  src/Pathtracing.c \
	  src/PointLight.c \
	  src/Ray.c \
	  src/Raytracing.c \
	  src/Renderer.c \
	  src/Scene.c \
	  src/Scene1.c \
	  src/Scene2.c \
	  src/Sphere.c \
	  src/Thread.c \
	  src/Time.c \
	  src/Triangle.c \
	  src/Utils.c \
	  src/Vec2.c \
	  src/Vec3.c \
	  src/Vertex.c \
	  src/XContext.c \

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
