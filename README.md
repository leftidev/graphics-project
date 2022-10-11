- Graphics rendering testing using GLFW and OpenGL
- Cross-platform (Linux, Windows)

ROADMAP
-------
1. 3D Cube (wireframe mode)
    - Visual indicator of vertex points?
2. Rotate, scale, move the cube
    - Automatically using a time function
    - Expand into doing it with a mouse/keyboard?
3. Create a camera class for moving around the scene


Notes
-----
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