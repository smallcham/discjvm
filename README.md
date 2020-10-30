# DiscJVM - (Dis) Distributed (C) Based On C (JVM)Java Virtual Machine

### DiscJVM 是一个基于jvm11规范以纯C语言编写的一个虚拟机的实现，目的是为了深入理解虚拟机原理，并在此基础上尝试将内存映射至多机，以实现指令级的分布式执行而无需对代码作任何修改（目前内存映射这部分尚未实现）。

### 如果你对这个项目感兴趣，说明你应该看过或者了解过不少jvm相关的书籍或信息，但纸上谈兵总让你有隔靴搔痒的感觉，作用不大，要真正了解jvm如何实现还是得从头到尾实现一个jvm，这也是我编写discjvm的一个主要原因。

### DiscJVM 不是一个完整的java虚拟机，不可以用作生产环境，目前的完成度仅限于执行一些简单的代码，大部分基础类库的本地支持尚未编写完全，主要目的还是用以理解和学习虚拟机相关技术。

### DiscJVM 的基础类库使用的是java.base.jmod，而不是rt.jar，这是因为jdk11已经将rt.jar移除，javac等编译工具都应该使用官方工具，所以如果你想要体验一下discjvm你需要先装好jdk11并设置好JAVA_HOME环境变量

### 目前仅支持Linux平台，并且只会支持Linux，跨平台不是此项目的目的。

## 目录说明:
/discjvm
-------/build
-------/model	#基础结构体以及链表哈希表等数据结构的定义和封装
-------/runtime #虚拟机主要执行逻辑代码
-------/share	#本地方法的映射与实现
-------/test	#测试用class
-------/util	#工具类库
-------/main.c

## 编译方法
> git clone https://github.com/smallcham/discjvm.git
> cd discjvm/build
> cmake ../
> make

## 使用方法(以测试class为例):
> cd discjvm/build
> ./discjvm ../test/class/HelloWorld

[![](https://smallcham.github.io/static/img/jvmtest1.png)](https://smallcham.github.io/static/img/jvmtest1.png)
[![](https://smallcham.github.io/static/img/jvmtest2.png)](https://smallcham.github.io/static/img/jvmtest2.png)


