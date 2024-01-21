This project
------------
- Graphics rendering testing using GLFW and OpenGL
- Cross-platform (Linux, Windows)

TODO
-------------
- Add building glfw3 to the project

ROADMAP
-------
1. 3D Cube
    - Visual indicator of vertex points
    - Wireframe mode
2. Rotate, scale, move the cube
    - Automatically using a time function
    - Expand into doing it with a mouse/keyboard?
3. Create a camera class for moving around the scene


Patch notes
-----------
21.1.2024

- Updated shader to have functions for enabling/disabling vertex attributes
- Cube now takes reference to shader for more convenient vertex attribute handling
- Redundant code removed from Cube initialization
- Started decoupling code to a renderer
    * Created texture, renderer classes

20.1.2024

- Added 3D cubes and 10 of them rotating on the scene

19.1.2024

- Added example of scaling and rotating the cube via MVP matrix
- Updated example of cube to use a correct MVP matrix in the shader for going 3D

13.10.2022

- Added texture loading via stb_image, texture binding

12.10.2022

- Modified rendering code to use element buffer objects
- Added wireframe mode
- Render a 2D cube instead of triangle

11.10.2022

- Moved reading shader sources from external shader files
- Re-structured and renamed project folders

4.3.2022

- Added mouse button callback for toggling between wireframe and fill mode
- General refactoring and renaming
- Implemented matrix translate via keyboard input
- NOTE: Scaling is still WIP and doesn't work correctly 

24.2.2022

- Tested linmath.h and mat4x4 functions for modifying MVP matrix in shaders/code
- Codebase in test mode, clean it up