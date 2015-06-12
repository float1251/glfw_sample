mac:
	cc `pkg-config glfw3 --libs --cflags` app.c -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

shared:
	cc -fPIC --shared `pkg-config glfw3 glu  --cflags ` -o libgame.so game.c `pkg-config --libs --static glfw3 glesv2`
