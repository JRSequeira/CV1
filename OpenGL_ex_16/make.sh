g++ -c loadOBJ.cpp -lm -lglut -lGL -lGLEW -o loadOBJ.o
ar rvs loadOBJ.a loadOBJ.o
gcc angleRotation.c callbacks.c consoleIO.c init.c mathUtils.c menus.c models.c Project_CV_64191_64645.c shaders.c shading.c -w -lm -lglut -lGL -lGLEW -g loadOBJ.a -o Project_CV_64191_64645 -lstdc++
