## DiscJVM
#### - (Dis) Distributed (C) Based On C (JVM) Java Virtual Machine

#### 简述
-------
1. DiscJVM 是一个基于jvm11规范以纯C语言编写的一个虚拟机实现，目的是为了深入理解虚拟机原理，并期望在此基础上尝试将内存映射至多机，以实现指令级的分布式执行而无需对代码作任何修改（目前内存映射这部分尚未实现）。

2. 如果你对这个项目感兴趣，说明你应该看过或者了解过不少jvm相关的书籍或信息，但纸上谈兵总让你有隔靴搔痒的感觉，作用不大，要真正了解jvm如何实现还是得从头到尾实现一个jvm，这也是我编写discjvm的一个主要原因。

3. DiscJVM 不是一个完整的java虚拟机，不可以用作生产环境，目前的完成度仅限于执行一些简单的代码，大部分基础类库的本地支持尚未编写完全，主要目的还是用以理解和学习虚拟机相关技术。

4. DiscJVM 的基础类库使用的是java.base.jmod，而不是rt.jar，这是因为jdk11已经将rt.jar移除，javac等编译工具都应该使用官方工具，所以如果你想要体验一下discjvm你需要先装好jdk11并设置好JAVA_HOME环境变量

5. 目前仅支持Linux平台，并且只会支持Linux，跨平台不是此项目的目的。

-------

#### 目录说明:

./discjvm

-------/build

-------/model	#基础结构体以及链表哈希表等数据结构的定义和封装

-------/runtime #虚拟机主要执行逻辑代码

-------/share	#本地方法的映射与实现

-------/test	#测试用class

-------/util	#工具类库

-------/main.c

-------

#### 编译方法

> `git clone https://github.com/smallcham/discjvm.git`

> `cd discjvm/build`

> `cmake ../`

> `make`

--------

#### 使用方法(以测试class为例):

> `cd discjvm/build`

> `./discjvm ../test/class/HelloWorld`

[![](https://smallcham.github.io/static/img/jvmtest1.png)](https://smallcham.github.io/static/img/jvmtest1.png)
[![](https://smallcham.github.io/static/img/jvmtest2.png)](https://smallcham.github.io/static/img/jvmtest2.png)

--------

#### 尚未实现

1. invokedynamic jdk11关于这部分的逻辑非常的绕，暂时没看明白，目前该指令尚未实现，这意味着包含动态调用部分的程序无法执行。

2. 本地方法并未100%实现， 目前编写的本地方法实现均在/share/native目录下。

3. gc尚未实现，目前的内存分配都是直接malloc，尚未开始着手内存回收部分。

4. 字符串常量池的区域划分逻辑尚未编写，这意味着目前字符串对象不会在地址上相等。



