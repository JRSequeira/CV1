g++ -c loadOBJ.cpp -lm -lglut -lGL -lGLEW -o loadOBJ.o
ar rvs loadOBJ.a loadOBJ.o
gcc angleRotation.c callbacks.c consoleIO.c init.c mathUtils.c menus.c models.c OpenGL_ex_16.c shaders.c shading.c -lm -lglut -lGL -lGLEW -g loadOBJ.a -o aa -lstdc++
