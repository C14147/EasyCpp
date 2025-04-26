EasyCpp
=====
[![Language](https://img.shields.io/badge/C++-ISO20-blue?logo=cplusplus)](https://python.org)
![PackageName](https://img.shields.io/badge/EasyCpp-1.0.0-green)
![Technology](https://img.shields.io/badge/{fmt}-blue)

<p>_A library that implements the powerful features of Python 3 in C++_</p>

## Introduction
C++ has faster speed, while Python has powerful libraries. This library aims to port some of the powerful features of Python to C++, making C++ programming faster.
## Get Started
### Method 1: Clone & Copy
Run the following code on the terminal:
```bash
git clone https://github.com/C14147/EasyCpp.git
```
Then, you can copy it into your project. No additional operation required!
### Method 2:Compile to Library
There is no code in the source file for generating static libraries or dynamic link libraries. If necessary, please manually edit and compile. Please note the open source agreement.
# Usage
Refer to the **wiki** of this repository.
# Examples
The warehouse already contains a test file (test.cpp). You can manually compile this file and check if the library is working properly.
In addition, in future updates, some mini programs written using this library may be added. Here is an example of a guessing game for numbers:
```c
#define PYTHON_FORMATED
#include"EasyCpp.h"
#include"String/String.h"
#include"FuncOptimize/func_io.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace easycpp;

int main(){
	srand(time(0));
	int num = rand() % 100;
	int guess = -1;
	print(str("Guess A Number(0-100):"));
	scanf("%d",&guess);
	while(guess != num){
		print(str("Wrong! Guess Again:"));
		scanf("%d",&guess);
	}
	print(str("Right! The number is: {}").format(num));
	system("pause");
	return 0;
}
```
