mac:
	cc `pkg-config glfw3 --libs --cflags` app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

linux:
	cc `pkg-config glfw3 --libs --cflags glesv2` -o app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
	./app

shared:
	cc -fPIC --shared `pkg-config glfw3 glu  --cflags ` -o libgame.so game.c `pkg-config --libs --static glfw3 glesv2`
