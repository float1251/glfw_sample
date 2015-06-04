all:
	cc `pkg-config glfw3 --libs --cflags` -o app app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	./app
