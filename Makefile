all:
	cc -I/usr/local/Cellar/glfw3/3.1.1/include/ -lglfw3 -o app app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	./app
