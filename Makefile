all:
	cc `pkg-config glfw3 --libs --cflags glesv2` -o app app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	./app
