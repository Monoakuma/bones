#pragma once
#include <GL/glew.h>
#include <iostream>
#define TestCall(x) GLClearError();x;GLLogCall() //must be used in a scope deeper than the main scope.
#define ASK(x,y) if (!(x)) std::cout<<"[ASK]:>>False Result. "<< y <<std::endl //ideally should return the location of the error but ehh not now.
void GLClearError();
void GLLogCall();
