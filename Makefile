all:
	cc `pkg-config glfw3 --libs --cflags glesv2` -o app.o app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	./app

linux:
	cc `pkg-config glfw3 glu  --cflags ` -o app.o app.c `pkg-config --libs --static glfw3 glesv2`
	./app.o

shared:
	cc -fPIC --shared `pkg-config glfw3 glu  --cflags ` -o libgame.so game.c `pkg-config --libs --static glfw3 glesv2`
