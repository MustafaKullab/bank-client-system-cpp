# Bank Client Management System

A console-based Bank Client Management System built with C++.

This project was created as part of my C++ problem-solving learning journey.  
I implemented this version independently before reviewing the instructor's solution.

## Features

- Show all clients
- Add new clients
- Prevent duplicate account numbers
- Delete clients
- Update client information
- Find clients by account number
- Save and load client data using a text file
- Console-based main menu

## Client Data

Each client contains:

- Account Number
- PIN Code
- Name
- Phone Number
- Account Balance

Client data is stored inside:

```text
Client.txt
```

The data format used in the file is:

```text
AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance
```

Example:

```text
A250#//#2536#//#Mohammed#//#0599999999#//#2500.000000
```

## Concepts Practiced

This project helped me practice:

- Structs
- Vectors
- Functions
- File handling
- Reading and writing files
- String manipulation
- Searching data
- Updating records
- Deleting records
- Menu-driven programs
- Passing variables by reference
- Breaking a large problem into smaller functions

## Technologies

- C++
- Standard C++ Library
- File handling with `fstream`

## How to Run

Compile the program:

```bash
g++ main.cpp -o bank
```

Run it:

```bash
./bank
```

On Windows:

```bash
bank.exe
```

Make sure `Client.txt` is available in the program's working directory.

## Project Status

Version 1 completed.

This version represents my own implementation before comparing it with the course solution. I plan to review and refactor the project as I learn better approaches.

## Learning Source

Built while studying the C++ Problem Solving course by Programming Advices / Abu-Hadhoud.
