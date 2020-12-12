# EmojiPop项目说明文档

> 同济大学2019级软件工程荣誉课大项目

## 项目信息

- 项目名：**EmojiPop**（一个类似于AniPop的游戏）

- 项目成员：

  - 1953288  张思源  
- 贡献比例：  
  
- 张思源  100% 
  
- 项目Github地址：<https://github.com/zsy326/my_AniPop>


## 项目开发文档

- 选用引擎：**Cocos2d-x 3.17.2**

- 支持平台：Windows

- 游戏整体架构设计： 

  -  主要是由几个Scene以及它们之间的切换完成
  - Scene里面有各自菜单，可以实现相互切换
  - GameScene为游戏主页面，Emoji精灵将以棋盘的形式分布在视图中间，通过触碰监控以达到移动精灵的功能，与开心消消乐一样，满足要求的精灵将被消去，在规定步数内达到制定分数即可过关
  - 每个Scene都设计了一个类，继承于Scene类
  - 精灵为单独一类EmojiSprite，继承于Sprite类

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
    - [x] 记录通关最短时间  
    - [x] 剩余步数奖励机制：当玩家通关时仍有剩余步数，在终局方块中随机产生特殊方块并消除，使⽤用户获得更更⾼高分数 
    - [x] 只会移动不会被消除的物品（雪花）
  - C++新特性
     - [x] 初始化列表
    - [x] 类型推断

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
  
 2. 使用Sprite Sheet 创建精灵

     通过 plist 等格式的文件索引的资源，使用图集比使用多个独立图像占用的磁盘空间更少，还会有更好的性能

  ```c++
 // loading plist and png
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
    spriteSheet = SpriteBatchNode::create("sprites.png");
    addChild(spriteSheet);

  ```

- 技术难点：
  
  1. 精灵消去条件的判断算法
  2. 遍历棋盘时对不同状态的精灵的相关标记
  3. 遍历棋盘时对特殊方块和普通方块的处理逻辑
  4. 关卡之间的切换和参数传递
  
  
  
- 曾经遇到过的问题及解决：
  
  1. 搭建环境时由于电脑某文件被误删过，就一直没有成功，一直找不到原因【通过将误删文件下载到相应位置解决】
  
  2. 播放背景音乐所需要用的`SimpleAudioEngine`中调节音量大小的函数` setBackgroundMusicVolume`是空函数【通过自行补全代码解决】
  
  3. 播放背景音乐没有采用UserDefault储存音量状态，导致一出调节音量的界面，音量就恢复默认大小【采用UserDefault来储存音量设定】
  
  4. 特殊消去的牵连消去遭遇死循环【仔细检查逻辑，反复调试解决】、
  
  5. 剩余步数奖励机制的实现过程中吗，动画没有达到预期效果，游戏体验感不佳【尚未解决】
  
    
  

- 项目运行截图  

  <img src="C:\Users\张思源\Desktop\WelcomeScene.png" style="zoom:50%;" />

  <img src="C:\Users\张思源\Desktop\主菜单.jpg" style="zoom:50%;" />

<img src="C:\Users\张思源\Desktop\主游戏界面.jpg" style="zoom:50%;" />

<img src="C:\Users\张思源\Desktop\过关界面.jpg" style="zoom:50%;" />

