<div align="center">

  <h1>
    <img src="./assets/rainbow.svg" width="45">
    𝖢𝖲𝟣𝟢𝟨𝖫 & 𝗋𝖾𝗅𝖺𝗍𝖾𝖽 𝗌𝗍𝖺𝖼𝗄𝗌
    <img src="./assets/rainbow.svg" width="45">

  </h1>

</div>

> TLDR: 一些对CS106L的点评; 一些学习CS106L时使用到的额外的资料; 还有一些写实践作业时碰到的问题以及对应的解决方式.

最近忙里偷闲总算是把Stanford的CS106L肝完了, 趁着记忆犹新打算把整个过程记录一下, 顺带点评一下这个课程.

Stanford的很多课程(如编译原理和计算机网络)都是以CS106L为先导课, 因此从理论上来说CS106L的课程质量应该是相当高的.
而事实上也确实如此, 这门课会介绍**C++20及之前**的各种特性(列表初始化、结构化绑定、移动语义、
左值右值、Lambda表达式、模版元编程、constexpr、concept、RAII...), 还会告诉你C++中的good &
bad practice. 学完之后确实能感受到C++发展至今已经变成了一门相当工程化的语言, 凝结了无数前人踩过无数坑后得到的智慧.
另外, instructor的slides(2023)写得也相当好, 在学习的过程中完全不需要去看课堂录播, 极大降低了学习成本.

更重要的是CS106L历经多年, slides和实践项目根据历届学生的反馈几乎年年更新,
每一届的instructors都为CS106L付出了相当多时间, 其中光是assignment2的测试程序就写了将近2000+代码,
简直就是把饭喂到嘴里.

再来说**这门课的一些不足**(个人感觉).

可能是因为课时所限, 这门课居然没有把C++的构建系统以及常用的C++构建工具(如CMake)作为一个主题来讲授,
只是在最后略有提及. 而事实上在写一个C++项目时, 如何优雅地对这个项目进行组织、构建、debug、
维护是一个相当头疼的问题.
虽然这些事情跟C++语言本身没有关系, 但也确实是在写代码时真实存在的.
其实这也是很多课程的一些通病, 即只讲某个事物本身却不去讲这个事物所依赖的工具链, 以至于在实践时会产生诸多问题.

另外就是这门课虽然会介绍C++20的一些新特性(如concept), 但居然没有介绍C++20的ranges.
个人感觉课程内容其实可以有一个更好编排(有些内容占用的课时有点多了,
比如Containers, Iterators and Pointers).
因此, 在学习CS106L的实际过程中我还看了一些非常优秀的开源项目以及tutorials,
最终算是把CS106L所缺失一些的东西弥补了回来.
> 额外用到的资料会在后文给出.

但总的来说, CS106L绝对算得上是一门好课. 尤其是在**assignment2中需要实现一个stl compliant的unordered_map**,
几乎可以把所有学到的东西都用上, 完成后可以明显感觉到自己的C++功力大增.
在2023版本中, instructor几乎给出了一个极其优雅的实现, 阅读完源码以后可谓是收获颇丰.

> 有关assignment{1,2}可能会碰到的一些问题会在后文进行讨论.

最后, 由于CS106L每年的变动都比较大(包括实践作业的难度), 并且有些年份的实践作业链接还会失效,
因此我把收集到的一些年份的实践作业和slides放到了[这里](./archive/),
大伙可以根据自己的牙口来选择喜欢的食用方式.

## 补充资料

### CMake相关

* [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html):
CMake的官方教程, 建议看看前面两个step.

* [cmake-examples](https://github.com/ttroy50/cmake-examples): 一个非常优秀的开源项目,
提供了多种场景下使用cmake的案例, 对于速入门cmake相当够用(强烈推荐).

* [cmake菜谱](https://www.bookstack.cn/read/CMake-Cookbook/README.md):
一本对cmake作了比较详尽阐述的书, 如果想要对cmake作更深入的了解可以看看.

* [CMake Tools for Visual Studio Code documentation](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/README.md):
在vscode中集成cmake的官方教程, 在**学会如何编写CMakeLists.txt以后一定要看**,
学完之后就可以开启C++项目的无痛build+debug.

### vcpkg相关

* [vcpkg官方仓库](https://github.com/microsoft/vcpkg?tab=readme-ov-file):
vcpkg是微软推出的一个C++第三方包的管理工具(C++版pip), 在官方仓库中有最基本的使用指南.
这个工具在assignment1中会用到, 虽然starter code中已经写好了build脚本,
但还是建议了解一下这工具, 因为在C++项目中集成和管理第三方依赖其实也是一个很麻烦的事情.

    > vcpkg也可以和CMake进行集成, 从而进一步简化在引入第三方依赖时的工作流.

* [vcpkg文档](https://learn.microsoft.com/zh-cn/vcpkg/):
这个官方文档内容并不多, 建议看看.

### C++相关

* [cppreference](https://en.cppreference.com/w/):
这个就不过多介绍了, 在使用和了解C++某些特性时必读的材料. 为了培养查阅cppreference的习惯,
在assignment1和assignment2中也会要求去阅读其中的某个部分.

* [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#S-resource):
列出了C++中各种情况下的good & bad practice, 并且阐述了为什么要或不要这么做的原因.
在CS106L中也引用了其中的一条准则来告诉我们为什么需要有RAII这样的实践.
平时抽空可以看看, 其中的很多准则在其它编程语言中也相当受用.

* [Modern C++ Tutorials](https://changkun.de/modern-cpp/en-us/01-intro/):
可以作为CS106L的补充资料.

## 关于assignment1

在assignment1中需要**完成一个[WikiRacer](https://www.thewikigame.com/group)的游戏**,
本来以为是要写一个最短路算法, 结果发现整个算法框架已经在starter code中写好了(不过启发式的规则确实没想到),
因此主要的问题可能还是在环境的配置上.

由于assigment1的starter code依赖cpr这个第三方包, 所以在build的过程中需要通过vcpkg下载对应的源码,
然后在CMakeLists.txt中引入依赖(这些都在setup.sh里写好了, 但还是建议阅读一下).

* **[问题1]** 使用vcpkg下载第三方包时下载失败: 先看一下终端上的日志, 找出下载超时的文件,
然后手动下过来放到vcpkg的downloads目录里, 再重新执行命令. 再有超时就继续反复这个过程.

* **[问题2]** 下载好依赖并生成CMakeLists.txt后, vscode的CMake Tool构建失败(日志显示找不到第三方包的头文件):
在CMakeLists.txt中显示指定find_package的PATHS变量(头文件位于vcpkg/installed目录中).

* **[问题3]** vscode的CMake Tool构建成功, 但是vscode的intellisense找不到第三方库的头文件,
导致vscode爆红:
在.vscode目录中配置c_cpp_properties.json, 显示指定includePath.

* **[问题4]** M系列Mac上运行测试文件失败: 二进制文件是基于x86的, 无法在arm架构上运行,
所以需要换一个基于x86的处理器来运行测试代码.

## 关于assignment2

assignment2中要求**实现一个stl compliant的unordered_map**, 并**提供了一个2000+行代码的测试**.
Handout的开头有这么一段话, 现在看来深感认同:

> According to veteran C++ programmers, there are two projects which bring together all the knowledge that a proficient C++ programmer should have:
> 1. Implementing a STL-compliant template class; and
> 2. Implement a macro to hash string literals at compile-time.

另外, assignment2的2022版本和2023版本提供的starter code不太一样, 2023版本的要求更低一些,
所以提供的starter code也就更加全面一点(2022版本的要求相较于2021版的也更低一些,
在更早的版本中要求实现HashMap的Iterator, 但学生反馈太花时间了).

但也正因为2023版本几乎由instructor提供了HashMap的完整实现, 因此整个代码写得相当巧妙,
强烈建议在开始编码前仔细阅读starter code, 会有相当大的收获.

由于提供了2000+行的测试代码, 因此在完成2023的assignment2后,
可以尝试把HashMapIterator和HashMap重新写一遍, 测试出现问题后再回去看starter code,
这样才能逐渐体会到starter code中的精髓.

在写assignment2的过程中, 遇到了一些个人感觉值得争议的点, 但由于内容有些冗长,
故放在[别处](./solutions/assignment2/README.md)进行讨论. 简单来说主要是两点:

1. starter code提供的代码是否符合RAII的实践?

2. 有关HashMap中移动赋值运算符的实现问题.
