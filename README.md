# Ataxx
同化棋，棋盘与棋子使用字符展现，实现了人机对战(简易版)、存档、读档、悔棋等功能，整个游戏使用上下左右按键、空格、回车、Backspace、Esc键操作。具体操作可编译运行后见游戏介绍。<br>

## 简介
　　本程序的全部功能通过上下左右方向键、空格键、Esc键、Backspace键与回车键实现，所有功能在DOS控制台实现，不需要对于选择输入编号或相应字符，操作简单易上手。打开程序会出现主菜单，除去欢迎语句外，共有5个选项，通过制表符制作出的光标随方向键上下移动，通过按下空格键进入指定功能，进入功能后可随时按Esc键返回主菜单。<br>

## 1、开始游戏
　　选择后会进入子菜单选择是否先手，亦是通过光标与方向键的结合以及空格键进行选择。选择是否先手后，进入棋盘画面，棋盘由字符画出，人与机器分别执不同子，棋盘下方将显示当前人所执子与电脑所执子，并且随着棋盘的更新显示每一方的棋子个数。玩家通过方向键控制光标上下左右的移动至想要走的棋处，通过按空格选子，再移动上下左右键到落子处按下空格落子，实现一步走棋，如果此步棋违规，程序会提醒玩家“此步违规，再试一次”，且此步棋不对棋盘产生影响。若玩家想要悔棋，可按下Backspace键进行一步悔棋，为了游戏的挑战性，玩家每走一步只可获得一次悔棋机会。<br>
　　玩家中途可按Esc键返回主菜单，若此时再选择开始游戏，程序会询问是否继续上次的游戏，玩家通过方向键与空格键选择，选择否则开始新游戏，进入选择是否先手的子菜单；选择是则进入棋盘继续上次游戏。每次游戏结束，程序给出最后比分并根据比分判断胜负，同时给出是否再来一局的选择，同样通过方向键和空格键选择，选择否则退回主菜单，选择是则如同开始新游戏。<br>
　　对于玩家的走棋，程序通过相应函数实现走子，产生对弈效果。<br>
 
 ## 2、存储游戏
 　　当玩家中途退出游戏但是想要保存棋盘时，从游戏中退出选择此项，程序会要求玩家输入为保存的文档起名，在此处为实现按Esc键退出的效果，采用了循环输入的方法，一旦遇到Esc键即退回主菜单，但这种输入方式会影响删改文件名，于是采用了遇到Backspace键将文件名最后一位删去并清除屏幕重新打出实现删改效果。文件名起好后按回车键即可保存文档。<br>
   
## 3、读取游戏
　　当玩家选择此项时，程序会要求玩家输入曾保存过的文档名，若文档不存在会提示无法打开，若文档存在，按回车即可进入游戏。进入游戏后若又退出，无需玩家再进行存储，程序会自动在此文档存下棋盘，方便下次取用。<br>
  
## 4、游戏说明
　　选择此项后玩家可以看到游戏规则以及本程序的操作方法，按Esc键退回主菜单。<br>
  
## 5、退出游戏
　　选择此项后退出游戏。