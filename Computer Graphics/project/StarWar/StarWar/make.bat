g++ -o StarWar.exe setup.cpp ^
render.cpp init.cpp actor.cpp enemy.cpp plane.cpp ^
-Wall -O2 -D FREEGLUT_STATIC ^
-static-libgcc -static -std=c++17 ^
-lfreeglut_static -lopengl32 -lwinmm -lgdi32 -lglu32