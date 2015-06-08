all:
	cc `pkg-config glfw3 --libs --cflags glesv2` -o app app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	./app

linux:
	cc `pkg-config glfw3 glu  --cflags ` -o app app.c `pkg-config --libs --static glfw3 glesv2`
	./app
