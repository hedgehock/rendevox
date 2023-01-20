cd rendevox
gcc -c ./src/window.c -O3 -std=c99 -o ./bin/window.o -lSDL2 -lSDL2_ttf -lm
gcc -c ./src/render.c -O3 -std=c99 -o ./bin/render.o -lSDL2 -lSDL2_ttf -lm
gcc -c ./src/vector3.c -O3 -std=c99 -o ./bin/vector3.o -lSDL2 -lSDL2_ttf -lm
gcc -c ./src/matrix4.c -O3 -std=c99 -o ./bin/matrix4.o -lSDL2 -lSDL2_ttf -lm
ar rcs ./bin/librendevox.a ./bin/window.o ./bin/render.o
cd ..
cp -r ./rendevox/src/rendevox.h ./app/src/rendevox.h
cp -r ./rendevox/bin/librendevox.a ./app/lib/librendevox.a
cd app
gcc -O3 -std=c99 ./src/*.c -o ./bin/app -L ./lib -lrendevox -lSDL2 -lSDL2_ttf -lm
cd bin
./app
