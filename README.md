# C Preprocessor

<p align="center">
  A Simple C Preprocessor Implementation Using C
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/badge/Compiler-GCC-green.svg" />
  <img src="https://img.shields.io/badge/Platform-Ubuntu-orange.svg" />
</p>

---

## 📌 Project Overview

This project implements a basic **C Preprocessor** using the C programming language.

The program accepts a C source file as input, performs preprocessing operations, and generates an output file with the `.i` extension.

The project demonstrates the basic working principles of preprocessing through a modular implementation.

## ✨ Features

- **Comment Removal:** Removes single-line (`//`) and multi-line (`/* ... */`) comments.
- **File Inclusion:** Supports basic local header file inclusion.
- **Object-like Macros:** Supports macros such as `#define PI 3.14`.
- **Function-like Macros:** Supports macros such as `#define SQUARE(x) ((x) * (x))`.
- **Output Generation:** Generates a preprocessed `.i` file.

## 📂 Project Structure

```text
C-Preprocessor/
│
├── main.c
├── comment_removal.c
├── comment_removal.h
├── file_inclusion.c
├── file_inclusion.h
├── macro_handler.c
├── macro_handler.h
├── myheader.h
├── inputfile.c
├── Makefile
└── README.md
```

## ⚙️ Requirements

- Ubuntu Linux
- GCC Compiler
- Basic knowledge of C programming

## 🚀 Compilation

Clone the repository:

```bash
git clone https://github.com/amalpv798-ai/C-Preprocessor.git
```

Navigate to the project directory:

```bash
cd C-Preprocessor
```

Compile the project:

```bash
make
```

This generates the executable:

```text
mypreprocessor
```

## ▶️ Execution

Run the program by providing a C source file as a command-line argument:

```bash
./mypreprocessor inputfile.c
```

The program generates the preprocessed output:

```text
inputfile.i
```

## 📄 Viewing the Output

To view the generated file:

```bash
cat inputfile.i
```

## 🧹 Cleaning Generated Files

To remove the executable, generated `.i` files, and temporary files:

```bash
make clean
```

## ⚠️ Limitations

- Conditional compilation is not implemented.
- Function-like macros support one parameter.
- Nested header file processing is not fully supported.
- System headers may remain as include directives for GCC to process.
- This is a basic educational implementation, not a complete replacement for the GCC preprocessor.

## 🛠️ Technologies Used

- C Programming Language
- GCC Compiler
- Ubuntu Linux
- Makefile
