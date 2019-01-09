# SDL_3D_WIREFRAME
SDL/C++ port of a 42 project used to render simple wireframe images of plain text heightmaps. Compiled and tested under GNU/Linux.

Usage: ./sdl_fdf *filename*

## HEIGHTMAPS

A valid heightmap will store the width and height of the map on the first line of text.

In the example below, the first line specifies a width of 19 and a height of 11.

Immediately following that is the plaintext heightmap. Each line of numbers corresponds

to each row of points on the heightmap, and each number is interpreted as the corresponding

point's height.

### Example:

![Input-Contents](https://i.imgur.com/V82pIMS.png)

### Output:

![Screenshot](https://i.imgur.com/h1RchDz.jpg)
