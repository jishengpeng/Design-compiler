# 2022.6.10后更新全部源代码
## 项目介绍
#### 这是吉林大学编译原理课程设计，设计一个能够对SNL语言进行编译的词法分析器，语法分析器。
#### Lexical.cpp是词法分析器的源代码。
#### Parser.cpp是语法分析的部分源代码，选取了一些比较重要的函数。
#### 编译原理设计与实践原理.pdf（阅读的书籍）。
## 设计原理
#### 词法分析器就是将输入编译器中的源代码转换成TOKEN序列。这个是利用动态数组进行存储，利用双指针和字符串匹配的一些知识。
#### 语法分析器是编译器的核心，我主要采用递归下降法进行分析，目的是将TOKEN序列转换成动态的语法分析树。这个需要对自顶向下的文法，Pridect集，递归下降法，数据结构（树），递归有着一定的理解。
## 项目后续（2，3，4不是近期打算）
#### 1.主要会在在答辩之后更新全部源代码。并且对于语法分析器的实现进行解释说明。
#### 2.优化语言的表达式和错误处理，因为时间有限，没有测试到一个语言真正所有的情形，后续会根据参考书中有诸多错误和测试进行完善。
#### 3.利用QT对此进行可视化。（好久没写一千行的控制台代码了）
#### 4.完成一个编译器的后续部分，包括语义分析器，中间代码生成，中间代码优化，目标代码生成。
