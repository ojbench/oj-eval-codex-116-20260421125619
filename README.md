# Problem 116 - GreedySnake

**ACMOJ Problem ID**: 2376

## Table of Contents

- [Problem 116 - GreedySnake](#problem-116-greedysnake)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [Submission Format](#submission-format)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

This problem tests algorithmic problem-solving skills.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **2376. GreedySnake** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/116/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

经典贪吃蛇小游戏！

规则如下：

1. 贪吃蛇初始长度为1，每吃一个食物长度加1;
2. 贪吃蛇每次移动一格，每次移动后，尾部减少一格;
3. 贪吃蛇碰到墙壁、边界或者自己的身体，游戏结束。如果反方向移动（比如前面是往下走，突然往上），直接判定为死亡;
4. 贪吃蛇每次移动的方向由玩家控制，玩家可以通过键盘上的方向键控制贪吃蛇的移动方向。为了方便测试，我们规定上下左右分别对应键盘上的$U$,$D$,$L$,$R$键，$N$键表示保持原有方向;

地图的界面如下：

1. 地图大小为$height$*$width$;
2. 地图上有若干食物，一开始食物的位置不能与贪吃蛇的身体重合，食物用*表示;
3. 地图上有若干障碍物，障碍物用#表示;
4. 贪吃蛇的头用@表示，身体用o表示;

请你根据给定的框架完成这个小游戏吧！

下发文件：[attachment]GreedySnakeDown.zip[/attachment] / [jbox](https://jbox.sjtu.edu.cn/l/l1DGfi)

hint：这段不用自己实现，main函数中已经实现了
```c++
bool is_food(Map* map, int x, int y);
//return true if the cell at (x,y) is food

bool is_wall(Map* map, int x, int y);
//return true if the cell at (x,y) is wall

void eat_food(Map* map, int x, int y);
//remove the food at (x,y)

int get_height(Map* map);
//return the height of the map

int get_width(Map* map);
//return the width of the map
```

代码中的enum class是枚举类，使用方式如instruction::LEFT

如果想了解更多可以点[这里](https://en.cppreference.com/w/cpp/language/enum)或[这里](https://www.runoob.com/w3cnote/cpp-enums-intro-and-strongly-typed.html)

std::pair详见[这里](https://en.cppreference.com/w/cpp/utility/pair)

hint:指针是是一种特殊的变量,其值为一个地址，所以可以用它来代指一个元素, &是获得一个元素的地址，*是获取一个指针变量指向的值,例如
```c++
int a[10]={1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
int pa* = &a[1];
printf("%d" , *pa);
```

hint：在函数
```c++
std::pair<int, std::pair<int, int> *> get_snake()
```
中，你不应该使用局部变量，应该使用new来创造数组。
这段代码应该会输出 2 。

请你完成src.hpp并上交，我们将运行Game.cpp测试代码

### Input Format

第一行包含两个整数$height$和$width$，表示地图的大小。
之后的$height$行，每行包含一个长度为$width$的字符串，表示地图的布局。
之后的一行包含一个字符，表示贪吃蛇的初始方向（L,R,U,D中的一种）。
之后若干行每行包含一个字符串，表示用户指令（L,R,U,D,N中的一种）。

### Output Format

输出每次移动后的地图布局。
在游戏结束时，输出“Game Over”，并输出得分。
得分的计算方式为贪吃蛇的长度加上存活轮数。

### Samples

#### Sample 1

**Input:**
```
5 5
#....
.*...
*.@..
.....
.#...
U
U
L
N
D
D
U
```

**Output:**
```
Round: 1
#....
.*@..
*....
.....
.#...
Round: 2
#....
.@o..
*....
.....
.#...
Round: 3
#....
@o...
*....
.....
.#...
Round: 4
#....
oo...
@....
.....
.#...
Round: 5
#....
o....
o....
@....
.#...
Game Over
Score: 8
```

### Data Constraints

地图大小 height,width <= 20 

轮数 <= 1000



## Resource Limits

- **Time Limit**: 1000 ms
- **Memory Limit**: 244 MiB

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 1000 ms
- **Memory Limit (per test case)**: 244 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/116/data_test/`.

Attachments and starter files for this problem are located at `/workspace/data/116/`.

## Submission Requirements

### Submission Format

Submit a single C++ source file to the Online Judge. The OJ provides its own `main.cpp` which `#include "src.hpp"`. Your submission will be written to `src.hpp` and compiled together with the OJ's driver code.

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
