*Update: This project is essentially unmaintained at this point, since I don't have time to work on it, and my focus has moved on to other things.  Note that this very code was long ago incorporated directly into OpenCV and, as far as I know, still serves as the basis of OpenCV's SIFT implementation.  Thus, if you have any issues with this project, I encourage you to use OpenCV's SIFT implementation directly.*

Intro
=====

This is a collection of code I've put together to detect SIFT features 
in images and to use SIFT (or other) features to compute image 
transforms with RANSAC. It includes a SIFT function library as well as 
some executables to detect, match, and display keypoints. For more 
information on SIFT, refer to the paper by Lowe:

Lowe, D. Distinctive image features from scale-invariant keypoints. 
International Journal of Computer Vision, 60, 2 (2004), pp.91--110.

Or see Lowe's website:
http://www.cs.ubc.ca/~lowe/keypoints/

Some of the code also works with affine-invariant features from the code 
by the VGG at oxford:
http://www.robots.ox.ac.uk:5000/~vgg/research/affine/index.html

Check out match.c for an example of how to use the RANSAC function.  Try 
`match beaver.png beaver_xform.png` to see it work.

Documentation is included in the docs/ directory.  If it is not there, 
use `make docs` to build it (you need Doxygen).

Help is available for executables using the '-h' command line option.


Requirements
============

All code in this package requires the OpenCV library (known working 
version is 2.3):
http://sourceforge.net/projects/opencvlibrary/

Some functions require GDK/GTK+2 (known working version is 2.18.4):
http://www.gtk.org/

Building
========

To build everything, use make:

	make

This should produce a few executables in bin/, a static library 
lib/libopensift.a, and some HTML documentation in docs/.  You can use the -h 
argument to get help with any of the executables.  libopensift.a can be 
compiled into your own code using the standard method:

	gcc -I/path/to/opensift/include/ -L/path/to/opensift/lib/ yourcode.c -o yourexecutable -lopensift

The documentation in docs/ describes all of the functions available in 
libopensift.a as well as #defines, etc.  Use the documentation to determine 
what header files from include/ to include in your code.

You can also individually build any of the executables or libopensift.a, 
e.g.

	make libopensift.a


License
=======

See the file LICENSE for more information on the legal terms of the use 
of this package.
