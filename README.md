# About
---
__Group Name:__ Seg Fault

__Authors__

* Jacob Fairbanks

* Ian Furguson

* Jacob Guenther

* Kyle Jones

* Bradely Morton

# Build Instructions
---
## Dependecies

* CMAKE

* SFML 2 (Simple Fast Multipmedia Library)
* OpenGL (Open Graphics Library)
* GLEW   (OpenGL Extension Wrangler Library)__NEW__
* GLM    (OpenGL Mathmatics)__NEW__

---
### Linux(ubuntu)

Install Dependencies

>sudo apt install cmake libsfml-dev mesa-common-dev libglew-dev libglm-dev

Change your working directory to CS202-Group-Project then

>mkdir build

>cd build

>cmake ..

>make

now run the program

>./platformer

---
### Windows

---
### Mac

************************** TO DO (In no particular order) **********************
1) Implement Bradley's physics engine
2) Implement a jump
3) Possibly work in Bounding boxes for AABB - AABB collision detection (See LearnOpengl 3.3 pdf, page 490)
	-Re-allign models to first quandrant in Blender Export, for consistency in bounds checking.
4) Get user input via text parser

Non-Essential Targets
1) Set up music
2) Make fancy shaders
3) Add more models