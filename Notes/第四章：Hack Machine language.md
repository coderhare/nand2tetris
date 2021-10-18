# 第四章：Hack Machine language

> 本章内容：了解一台Computer所需要的所有基本部件：CPU，ROM，RAM，I/O deivices。然后完成部件，并且最后搭建成hack computer。



<img src="https://github.com/coderhare/nand2tetris/blob/main/Images/hack_contents.png" />

**内存地址空间的分布：（在hack computer的架构中，指令内存和数据内存是分割开的）**

- 指令地址空间
- 数据地址空间



**指令类型（只有两种）：**

- A- 指令： 地址指令
  - 用法：`@value`

- C- 指令： 计算指令
  - 用法:  `dest = comp ; jump`

**@value语法：**

- 导致$A$寄存器的值更新为$value$
- 导致被隐式选择的寄存器为$M[A]$(side effect)：也就是说$M$默认为$M[A]$
- 该指令还可用于创建变量和标签



**`C指令`各位域详解：**

![image-20211011190905670](https://github.com/coderhare/nand2tetris/blob/main/Images/C_instruction.png)

**一些预定义的标签：**

![image-20211011201712082](https://github.com/coderhare/nand2tetris/blob/main/Images/hack_builtin_symbols.png)



其中比较重要的有：**分支**和**循环**。

该操作都通过核心的`jump`指令来完成。



**I/O内存映射**

<img src="https://github.com/coderhare/nand2tetris/blob/main/Images/hack_screenMemory_map.png" />

我们的`RAM`是16位的，使用`2^{13}*16`个位，映射为屏幕的`256 * 512`个点阵



**键盘**

预定义宏`@KBD`代表键盘的占用内存的起始位置，实际上该内存的大小仅为1。

<img src="https://github.com/coderhare/nand2tetris/blob/main/Images/hack_character_set.png" />

**变量的抽象**

本质上是在内存中申请了一片区域，然后通过CPU和GPU等进行各种操作。在hack语言中，通过`A`寄存器指定变量的内存偏移量，然后可以直接通过`M`即`M[A]​`来操作A指向的内存区域，使得其值发生改变。





#### 源码

`Mulit.asm`: [这里](https://github.com/coderhare/nand2tetris/blob/main/Documents/Code/04/Fill.asm)

`Fill.asm`：[这里](https://github.com/coderhare/nand2tetris/blob/main/Documents/Code/04/Fill.asm)
