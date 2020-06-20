# Emoji项目说明文档

> 同济大学2019级软件工程荣誉课大项目

## 项目信息

- 项目名：**EmojiPop**（一个类似于AniPop的游戏）

- 项目成员：

  - 1953288  张思源
-小组成员贡献比例  

  -张思源 100%

- 项目Github地址：<https://github.com/zsy326/my_AniPop>

- 项目进度时间线：

  ![timeline]()
## 项目开发文档

- 选用引擎：**Cocos2d-x 3.17.2**

- 支持平台：Windows

- 游戏整体架构设计：  


- 评分项完成度

  - 基础功能
    - [x] 游戏开始界面
    - [x] 背景音乐、音量量控制
    - [x] 暂停及恢复功能、退出功能
    - [x] 至少4种不同类别的方块 [实现5种(不包含特殊方块)]
    - [x] 同类方块三消及三个以上的消除
    - [x] 超过三个相同方块消除时产生特殊方块，特殊方块在消除时产生强力效果
      实现了：
        1.消除一行/列
        2.消除周边一定范围(3*3)方块
        3.消除所有同类方块
    - [x] 随机产生新的方块
    - [x] 方块的移动动画
    - [x] 得分统计
    - [x] 关卡步数限制
    - [x] 至少2个关卡，每次进入关卡时方块的分布是随机的
  
  - 基础功能以外的可选功能 
    - [x] 记录最高分
  - C++新特性
    - [x] 类型推断
    - [x] 基于范围的for循环
  - 其他亮点
   
- 代码亮点

  1. Const.h头文件的使用

     将游戏里关于界面大小、精灵规模、精灵类型等常量属性放在`Const.h`头文件中

  ```c++
    #define BOARD_SIZE 8 // the number of sprites at each column/row
  #define SPRITE_SIZE 53 // the size of each sprite
  #define EMOJI_GAP 12 // the gap between two sprites

  #define GAME_SCREEN_WIDTH 600 // the width of screen
  #define GAME_SCREEN_HEIGHT 800 //the height of screen
  ```

  ```

- 曾经遇到过的问题
  1. 播放背景音乐所需要用的`SimpleAudioEngine`中调节音量大小的函数` setBackgroundMusicVolume`是空函数，若要调节背景音乐的大小需要自行补全代码。

-项目运行截图  

![]()
![]()
![]()
![]()
