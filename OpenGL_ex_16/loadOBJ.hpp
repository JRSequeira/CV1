#ifdef LOAD_H
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

extern void loadOBJ(const char* path,
             int * numvertices,
             GLfloat ** vertices,
             GLfloat ** normais);


