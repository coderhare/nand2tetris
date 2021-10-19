# 第五章：Hack Computer Architecture

> 本章内容：实现Memory以及CPU，并且按下图的结构进行连接。注意实现思路最好从Memory到CPU，CPU的实现是所有硬件电路里头最困难的一部分，建议通过教材推荐的电路结构进行编写。

![hack计算机架构](https://github.com/coderhare/nand2tetris/blob/main/Images/hack_computer_architecture.png)





### Memory

使用一块`16K`的`RAM`，两块`4K`的`SCREEN​`芯片，和​`1`的`Keyboard`芯片进行仿真。

这里简单讲讲思路。

整个`Memory`被划分为了三个部分：

- `0x0000-0x3fff`的区域为正常可使用的区域
- `0x4000-0x5fff`的区域为显示器的映射内存
- `0x6000`的区域为键盘的映射内存

可以发现，对于三部分内存，最高的`4bit`都是不一样的，可以利用这一点进行区分不同的内存区域再细分。



### CPU

> 建议不是学有余力的同学别折腾流水线这些高级一点的实现，这里的实现已经很清楚了。

![image-20211019161253689](/Users/wocaibujiaoquanmei/iCloud 云盘（归档）/GitHub/nand2tetris/Images/CPU_implementation.png)

**CPU的内部结构**：

- A寄存器，用于存放随机数值，以及指定内存单元M[A]
- D寄存器，用于存放数值，可用于参与中间运算
- PC，协助CPU读取指令
- ALU，完成各种数值运算
- Mux，实现`if-else`逻辑

在实现CPU之前，先来想想，CPU要解决什么问题，对应到指令上就是`A指令`和`C指令`。

**A指令**

![image-20211019163722056](/Users/wocaibujiaoquanmei/iCloud 云盘（归档）/GitHub/nand2tetris/Images/A_insturction.png)



**C指令**

将`instruction`的各个位域分解到对应的C指令位域

![image-20211019163829392](/Users/wocaibujiaoquanmei/iCloud 云盘（归档）/GitHub/nand2tetris/Images/C_instruction2.png)

<img src="/Users/wocaibujiaoquanmei/iCloud 云盘（归档）/GitHub/nand2tetris/Images/C_instruction.png" style="zoom:50%;" />

要先区分好`C指令`和`A指令`然后再进行处理，**要保证ALU标志位在A指令时不使输出发生变化，否则将导致产生奇怪的输出，因为ALU的6个标志位产生的64种情况都有对应输出，对于表上不存在的映射，是未定义行为，比方说我就得到过-2的奇怪数值。**

（实际上PPT上的内容已经很详细了，一定要去看看！）

为了区分`A指令`和`C指令`，在硬件层面需要处理的数值计算不做详细叙述，因为架构和思路已经说完了，剩下的工作应当是很简单的。感兴趣可以看看源码。

[源码文件夹]()



### Hack computer

![hack计算机架构](https://github.com/coderhare/nand2tetris/blob/main/Images/hack_computer_architecture.png)

非常简单的连线，按着这个图做即可,代码很短

![image-20211019164730890](/Users/wocaibujiaoquanmei/iCloud 云盘（归档）/GitHub/nand2tetris/Images/CHIP_COMPUTER.png)