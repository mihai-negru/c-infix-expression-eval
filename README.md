# **c-infix-expression-eval**
A simple C Language program to compute the infix expression using stacks

## **Table of Contents**

1. [Getting Started](#start-description)
2. [Building](#build-description)
3. [Testing](#test-description)
4. [Running](#run-description)

<a name="start-description"></a>

## **Getting Started**

The project is a **CLI app** to evaluate an **infix** expression (a subroutine that every compiler does for expression evaluation).
The infix expression should be a valid one and the **numbers** and **operators** should be separated by the following separators:

* <\n>
* <\space>
* <,>
* <;>
* <:>
* <`>
* <'>
* <">

Numbers can be **integers** or **floating point** if the selected mode is **integer** than no floating point number should be in the infix expression. However
in the **floating point** expression can exist integer numbers (without . sign).

More information about running the program will be discussed in the ***Running*** section.

The accepted operators are:
* **^** - power sign
* **P** - unary plus operator
* **M** - unary minus operator
* **N** - unary bitwise negation operator (for integer)
* __*__ - multiplication sign
* **/** - division symbol (program check for division by 0)
* **%** - modulo symbol (for integer) (check for modulo 0)
* **+** - binary plus operator
* **-** - binary minus operator
* **<** - bitwise left shift (for integer)
* **>** - bitwise right shift (for integer)
* **&** - bitwise AND (for integer)
* **v** - bitwise XOR (for integer)
* **|** = bitwise OR (for integer)

<a name="build-description"></a>

## **Building**

### **Dependences**

To build the current project and to get the **convertor** executable you have to check the following:
* You are running a Linux or WSL System.
* You have downloaded and loaded the [**c-language-data-structures**](https://github.com/Matrix22/c-language-data-structures) necessary for stack object.

### **Get executable**

To get the executable you should first clone the current project via https:

```BASH
    git clone https://github.com/Matrix22/c-language-data-structures.git
```

Then change the directory to the build folder and run the make command:

```BASH
    cd build
    make
```

The above commands will generate the **convertor** executable which is the app needed for the infix evaluation.

<a name="test-description"></a>

## **Testing**

For testing the program I have provided you two files in the **build** folder:
* infix.txt - the infix string expression with mixed commands (integer and double).
* numtype.txt - containing the mode selector **2** for mixted commands.

To run the test and to get also the valgrind log message you must run after generated the executable file:

```BASH
    make runv
```

<a name="run-description"></a>

## **Running**

The project is a **cli** application so you should provide command line params:

* First param must be the infix expression and should be a valid one

>**NOTE:** A valid infix expression must containg just operators specified ffrom the **Getting Started** section, integer or floating point numbers and JUST rounded paranthesis **()**.
The following members of a valid exoressions must be separated by the separators described int the **Getting Started** section.
A mini example would be : **( 90 + M 50) + 12 * 43 * M 32 + 12 * 43 * ( M 32 ) - 4 ^ 4 + M 4 ^ 4**.

* Second param must be the mode selector:
    * **1** - integer mode you are allowed to pass just integer numbers for the infix expression
    * **2** - floating point mode you are allowed to pass any numbers however the you should not write double numbers for the integer only members

>**NOTE:** A bad example of floating point mode expression would be : **100.12 % 32.1**. The following exaple will be calculated as **100 % 32 = 4**

If the infix expression is invalid the program will shut down at the:
* Conversion of the infix to postfix if other characters then specified are in the expression
* Evaluation of the postfix expression if any operation order or operation definition (applied * sing as a unary operator) was present in the expression

If the program failed it's execution some error messages will be printed in the **stderr** to show you that something went wring.

Example of running the application:

```BASH
    mv ./build/convertor path/to/your/directory
    cd path/to/your/directory

    ./convertor "100 + 20 % 21" 1

    # or

    ./convertor "100 + 20 % 21 - 20 * 13.23" 2 
```
