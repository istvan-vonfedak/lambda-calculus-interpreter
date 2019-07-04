# lambda-calculus-interpreter
This is a C++ program that interprets and reduces lambda calculus expressions.
It allows a user to input lambda expressions and it reduces them until no more
beta-reductions are possible, then it outputs the result.

## Compilation

Go into the src folder and type the following command into the
terminal:

    $ make

To clean the src folder type the following command into the
terminal:

    $ make clean

## Usage

Go into the src folder and type one of the following two
commands:

    $ ./lambdaReducer

  or

    $ ./lambdaReducer -debug

## Sample run
    - Type exit to quit program.

     input: (#x.(x (x y)) #a.(a a))
    output: ((y y) (y y))
