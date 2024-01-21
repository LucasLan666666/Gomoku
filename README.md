# 五子棋说明

## 简介 :page_facing_up:

1. 中国科学院大学 2023 年秋季武成岗老师班 C 语言大作业
2. 由于原始棋盘在终端显示过窄，借用了 [@Squareless-XD](https://github.com/Squareless-XD) 学长的创意，在同一行每相邻两个纵向落子的位置间增加了一条横线
3. 关于棋盘一些基础函数由老师提供，代码中用到的字符艺术来源于互联网，其余内容均由本人撰写
4. 关于五子棋开发文档的详细说明正在编写中，如果有任何修改建议，欢迎联系我

## 注意事项 :heavy_exclamation_mark:

1.  `Linux` 环境下，请将终端的字符编码格式设置为 `utf-8` ，字符显示设置为 **窄字符**
3. 请确保程序执行目录下具有创建和读写文件与文件夹的权限，否则不能使用记谱与悔棋功能
4. ***请不要在游戏过程中修改或者删除 `game_record` 文件夹以及该目录下的文件，否则会导致严重错误！*** :cold_sweat:

## 使用方法 :pushpin:

### 进行游戏 :video_game:

1. **编译** ：打开仓库 `Gomoku` ，在终端输入如下指令：

   ```shell
   make
   ```

2. **运行** ：

   - `Linux` 下，在终端输入如下命令：

      ```bash
      ./gomoku
      ```

   - `Windows` 环境下，可以直接点击 `gomoku.exe` 运行，或者在 `PowerShell` / `cmd` 输入如下命令：

      ```powershell
      .\gomoku
      ```

### 记录棋谱 :pencil2:

- 游戏中会提示玩家可以创建棋谱并命名，默认在 `gomoku` 程序所在目录下建立一个名为 `game_record` 的文件夹。
- 文件夹内会以 `txt` 文件存储对局，存储在目录 `game_record` 之中。

### 读取棋谱 :blue_book:

`Linux` 环境下，在命令行输入：

```bash
cat game_record/您的存档名.txt - | ./gomoku 
```

## 更新日志 :calendar:

- 2023.12.11：
    - 对实验课当堂内容进行整理，实现了选择游戏模式、退出游戏以及落子的功能
    - 目前尚不能判断五子连珠，人机对战模式和悔棋功能均在开发中

- 2023.12.14:
    - 对游戏界面进行了优化
    - 增加了 **记谱功能**
    - 修复部分bug

- 2023.12.31:
    - 完成了 **五子连珠判定** 和 **悔棋** 功能
    - 已经能支持 **双人模式** ，并判断 **胜负**

- 2024.01.03:
  - 增加了 **读谱** 功能（仅限于显示出棋局，但是有 bug，怀疑和 `pipe` 的工作方式有关系）

- 2024.01.06:
  - 实现 **随机落子** 功能（大猩猩 :monkey_face: ）

- 2024.01.10:
  - 实现 **禁手检测** 功能，包括复杂禁手
- 2024.01.14:
    - 实现基本的 **人机对战** 功能，下棋能力可以达到小学生水平（应该吧 :sweat_smile: ）

## 参考资料 :books:

- [International Rules of Renju - RenjuNet](https://www.renju.net/rifrules/)
- [lihongxun945/gobang: javascript gobang AI，JS五子棋AI，源码+教程，基于Alpha-Beta剪枝算法（不是神经网络） (github.com)](https://github.com/lihongxun945/gobang?tab=readme-ov-file)
- [【断奶班】五子棋零基础自学一本通（转载） - klchang - 博客园 (cnblogs.com)](https://www.cnblogs.com/klchang/articles/4542994.html)
- [五子棋复杂禁手的判断例题一则 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/527374023)

