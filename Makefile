NAME = sdl_fdf

SRCS = \
		srcs/main.cpp		\


all: $(NAME)

$(NAME):
	g++ $(SRCS) -o $(NAME) `pkg-config --cflags --libs sdl2 ` -lSDL2 -lSDL2_ttf -LSDL2_image 


