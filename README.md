**C Preprocessor**



\## Project Overview



This project implements a basic C Preprocessor using the C programming language.



The program accepts a C source file as input, performs basic preprocessing operations, and generates an output file with the `.i` extension.



\## Features



\- Removal of single-line comments (`//`).

\- Removal of multi-line comments (`/\* ... \*/`).

\- Basic local header file inclusion.

\- Object-like macro substitution.

\- Function-like macro substitution with one parameter.

\- Generation of a preprocessed output file.



\## Project Structure



\- `main.c` – Main program and processing sequence.

\- `comment\_removal.c` – Removes comments.

\- `comment\_removal.h` – Comment removal function declaration.

\- `file\_inclusion.c` – Handles header file inclusion.

\- `file\_inclusion.h` – File inclusion function declarations.

\- `macro\_handler.c` – Handles macro definitions and substitutions.

\- `macro\_handler.h` – Macro handler function declaration.

\- `Makefile` – Compiles the project.



\## Compilation



Open the terminal in the project directory and run:



make



This generates the executable named `mypreprocessor`.



\## Execution



Run the program by providing a C source filename:



./mypreprocessor inputfile.c



The program generates:



inputfile.i



\## Viewing the Output



cat inputfile.i



\## Cleaning Generated Files



make clean



\## Limitations



\- This is a basic implementation of a C preprocessor.

\- Function-like macros support one parameter.

\- Conditional compilation is not implemented.

\- Header inclusion is limited; nested header processing is not fully supported.

\- System headers may be left for GCC to process.



\## Technologies Used



\- C Programming Language

\- GCC Compiler

\- Ubuntu Linux

\- Makefile

