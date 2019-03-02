# cpp-makefile-module-oop
# MY README TEMPLATE 

<img src="https://raw.githubusercontent.com/Saikat2019/MY_README_TEMPLATE/master/README_RES/icon.jpeg" align="right" />

[![Language](https://img.shields.io/badge/C%2B%2B-17-0000ff.svg)](https://isocpp.org/)
[![Language](https://img.shields.io/badge/Makefile-g++-009900.svg)](#)

## Table of Contents
- [Explanation](#Explanation)
- [References](#References)
- [Feedback](#Get-Feedback)
- [Contribute](#Contribute)
- [License](#License)

## Explanation

When we separate a set of code into its own files, we call it a module. Although modules can contain sets of functions or sets of classes, we often use a single module for each class.  Modules are sometimes called libraries, although the term library is used more often for code that is in an already-compiled form. 

className.h
    These are the header file (or interface) for the module. Those who want to use the class (i.e., in a main program or another module) will have to #include this header file. It contains the class definition. 
className.cpp
    These are the implementation file for the module. Those who use the Point class must link their code with this code. It contains all the internals of the class, such as the method definitions.
    Since this module only contains the Point class, we'll also need a module for our Rectangle class, and a file for the main program (let's call it main.cpp).  
    Since main.cpp uses the Point class, it includes the Point header:
```cpp
    #include "Point.h"
```
When including a non-standard header file (like one you wrote), list its name in double quotes (like above). When including system header files, list their names in angle brackets, as  in:
```cpp
    #include <iostream.h>
```
### wrapping header files
 The code in a header should only be included into a .cpp file once; otherwise, the compiler may complain and refuse to compile the .cpp file. If a header does get included into a .cpp file more than once, we call this multiple inclusion.

Multiple inclusion is likely in the following form:
```cpp
    #include "Point.h"
    #include "Rectangle.h"
```
where Rectangle.h includes Point.h. In this case, you might get some compiler error like:
```cpp
    In file included from Rectangle.h:11,
                     from main.cpp:10:
    Point.h:9: redefinition of `class Point'
    Point.h:20: previous definition here
```
I.e., it did not like the fact that Point gets defined twice in main.cpp.

To solve the problem of multiple inclusion, we wrap the header by doing the following... Put the whole header inside an if-not-defined construct, like:
```cpp
    #ifndef POINT_H
    #define POINT_H

    CONTENTS OF Point.h

    #endif
```
where POINT_H is unique to the file Point.h. 

 Being wrapped, the first time Point.h is included:
```cpp
    #include "Point.h"  // POINT_H not defined yet,
                        // but once this #include is
                        // done it will be.
```
the symbol POINT_H will not be defined and the code in the header will be compiled. Later, if the header is included again (directly or indirectly):
```cpp
    #include "Rectangle.h"  // This tries to include Point.h.
```
in the same source file, then the code will be skipped since POINT_H is already defined (i.e., it got defined the first time we included Point.h).

### Compiling
 Now we would like to compile and link our program, which is made up of multiple files, i.e., header (.h) and implementation (.cpp) files.

We can use g++ as usual, and just need to specify the source code files that make up the program...
```bash
     g++ -o main main.cpp Point.cpp Rectangle.cpp
```
Note: We DO NOT list the header files. Since they are included into the above files, they will get compiled. Also, the -o main tells it to generate an executable named main instead of a.out.

We now have an executable main that can be run:
```bash
     main
```
Enter some values to test it.

Now, let's change the code. Go into Rectangle.cpp and change the method area() so that it uses the Rectangle method width() (ignore the height() method for now).

Once you've made the change, we could use the same command to recompile:
```bash
     g++ -o main main.cpp Point.cpp Rectangle.cpp
```
But wait! This is wasteful because nothing in main.cpp or Point.cpp changed, only Rectangle.cpp, so why should we recompile those other files?!

### Compiling source code separately:

What we should have been doing instead is to use separate compilation, i.e., compile source code to intermediate object files and then link them together.

First, recall that the program is made up of 5 source files:
    main.cpp, a main program.
    Point.h, header file for the Point class.
    Point.cpp, implementation file for the Point class.
    Rectangle.h, header file for the Rectangle class.
    Rectangle.cpp, implementation file for the Rectangle class. 

We want to compile each piece of the program separately and then link them together. This will allow us to only regenerate the parts of the program that are affected when we change some source code.

When we just compile source code (without linking it together), it means that we take the .cpp files and generate intermediate object files (.o).

To just compile source code, use the -c flag with the compiler...
```bash
     g++ -c main.cpp
     g++ -c Point.cpp
     g++ -c Rectangle.cpp
```
This will generate the object files:
    main.o (for main.cpp),
    Point.o (for Point.cpp), and
    Rectangle.o (for Rectangle.cpp) 

List your files to see the intermediate object (.o) files.

Finally, to link the object files (.o) into an executable that we can run, we use the compiler again (although this time it will just pass the .o files on to the linking stage):
```bash
     g++ -o main main.o Point.o Rectangle.o
```
What changes require recompiling/relinking:

Since we have just compiled the executable main separately on the commandline, we know exactly what commands are needed to generate the pieces that make up the executable.

Now, let's ask what we need to recompile (or relink) after we change certain files that make up our program...

For example, suppose we change the file main.cpp...What has to be regenerated?

Answer: First, recompile main.cpp to get main.o. Then, relink all the object files together again to get the executable main.

Now, suppose we changed Point.h?

Note: Whether a .cpp file changes or a header file included (directly or indirectly) by that .cpp file changes, we have to regenerate its corresponding .o file.

For example, since Rectangle.cpp indirectly includes Point.h (i.e., Rectangle.cpp includes Rectangle.h, which itself includes Point.h), then when Point.h changes, Rectangle.o must be regenerated.

Make Files:

Since it is tedious to recompile pieces of a program when something changes, people often use the make utility to do it for them.

The make utility requires that you have a make file that tells it how to compile/link the program.

Aside: Note the difference between the make utility (a program you run) and a make file (that tells the make utility how to compile/link a specific program).

A make file should be named either Makefile (first letter uppercase) or makefile (all lowercase). The make file should be in the same directory as the source code files.

Remember, we already gave you a file called Makefile.

Aside: Make files can have other file names, but then you'll have to tell the make utility what the name of the make file is (using a commandline option).

Try using make (with the Makefile you downloaded earlier). First, remove the old executable and object files:
```bash
    rm main *.o
```
Then, run make with the command:
```bash
    make
```
Since nothing has been compiled/linked, it will do:
```bash
    g++ -c -o main.o main.cpp
    g++ -c -o Point.o Point.cpp 
    g++ -c -o Rectangle.o Rectangle.cpp 
    g++ -o main main.o Point.o Rectangle.o
```
Aside: The -o flags it uses with the first 3 g++ commands just make it explicit what the object file names will be. If you have trouble, make sure that the make file is named Makefile and is in the same directory as the source code files.

Note that it compiled the 3 .cpp files into object files, and then linked the object files into an executable named main.

Now, type the make command again (let's explicitly tell it what to generate this time) and you get:
```bash
    make main
    make: `main' is up to date.
```
Here, make tells you nothing has changed, so it has no work to do.

Next, suppose we want the area() method in the Rectangle class to use the height() method...

Go ahead and edit the area() method in Rectangle.cpp now. Make sure you save the editted file to disk.

After editing, when we use make:
```bash
    make
    g++ -c -o Rectangle.o Rectangle.cpp 
    g++ -o main main.o Point.o Rectangle.o
```
it doesn't bother regenerating main.o or Point.o, since the files those depend on have not changed. 

[↥ back to top](#table-of-contents)

## References

http://www.cplusplus.com/doc/tutorial/classes/
https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
https://www.cs.bu.edu/teaching/cpp/separate-compilation/
      - *some good sources*

[↥ back to top](#table-of-contents)

## Get Feedback

 -	### Give me feed back here.
	 - [My Email](mailto:saikatmondal410@iitkgp.ac.in) 
	 - [My Facebook ID](https://www.facebook.com/profile.php?id=100011440244328) - *feel free to ping*
 -  ### Me
 	<p>
		<img src="https://avatars2.githubusercontent.com/u/33754597?v=4" width="100" height="100" />
	</p>

[↥ back to top](#table-of-contents)

## Contribute

Contributions are always welcome!
Please *create an issue if you find one*.

[↥ back to top](#table-of-contents)

## License

>License of the Project goes here.

[MIT](https://choosealicense.com/licenses/mit/)

[↥ back to top](#table-of-contents)

