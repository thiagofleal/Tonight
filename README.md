# Tonight: The highest-level C library in someplace
 ![alt tag](/Images/Logo.png)

The Tonight Library was created to make hight-level C programming easy code.
This library implements the following resources:

 ### Error tratement
  
  * **try** statement
  * **catch** statement
  * **finally** statement
  * **throw** statement
 
 ### Object-like programming style
  
  * interfaces
  * pseudo-objects
  * **new** statement
 
 ### String handle functions
  
  * concat
  * equal
  * retConcat
  * toString
 
 ### Implicit pointers
 
  * Generic pointers
  * Pointers to strings
  * Pointers to functions
  * Pointers to objects
 
 ### Object oriented programming
  
  * classes
  * interfaces
  * inheritance
  * polymorphism
 
 ### Lots of data types defined
  
  * Strings types
  * Exceptions types
  * Interfaces
  * Pseudo-classes
  * Resources classes
  
 ### Dynamically memory allocation whith error tratement
  
  * Arrays allocation
  * Matrixes allocation
  * Memory allocation
 
 ### Input and output
  
  * Scanner pseudo-class
  * Writer pseudo-class
  * Input resources class
  * Output resources class
  
 ### Generic resources implemented
  
  * *Tonight* pseudo-object
 
And all of it is implemented in pure C.

## Start

To start use the Tonight library, dowload the source code of the following files according to your operating system:

 * tonight.h
 * tonightdef.h
 * tonightOO.h
 * tonight.c

Compile the file "tonight.c" to an object file (tonight.o) and make a static library (libtonight.a).
Save the file "libtonight.a" in the folder of libraries your compiler.
Save the files "tonight.h", "tonightdef.h" and "tonightOO.h" in a folder named "Tonight" in the folder of includes of your compiler.

## Including the Tonight library

To include the Tonight library, use the following line in your source code:
 
 * Linux
  ```C
  #include <Tonight/tonight.h>
  ```
 * Windows
  ```C
  #include <Tonight\tonight.h>
  ```

To link the library, use the following link command:

 > -ltonight

 ## Documentation
 
 * [Documentation](Documentation)
 
 ## Author: Thiago Fernandes Leal
 
 ## Licence
 
 Copyright (C)  2018  Thiago Fernandes Leal.
	Permission is granted to copy, distribute and/or modify this document
	under the terms of the GNU Free Documentation License, Version 1.3
	or any later version published by the Free Software Foundation;
	with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
	A copy of the license is included in the section entitled "GNU
	Free Documentation License".
