# SG-Engine2D  
---
Simple Game 2D Engine 是我的写的一个简易的游戏物理引擎，其中包括一些2D游戏所具备的基础功能。  
  
## 功能介绍：  
  
## 使用方法：  
  
## 目录结构：  
- Map.h/Map.cpp：  
  可以用于任何图形库的游戏数据结构，这里只给出了raylib的接口。  
  
- Scene.h/Scene.cpp：  
  基于raylib图形库，给出的main与Map之间的接口。  
  
- RaylibTools.h/RaylibTools.cpp：  
  基于raylib图形库制作的工具类，可以让我在开发中更方便地使用raylib的函数。  
  
- RaylibPixelModel.h/RaylibPixelModel.cpp：  
  像素模型类，储存一些像素数据，可以绘制简单的像素图片，在项目中可以代替图片。  
  只在使用时加载所用的像素数据，不会将全部模型加载到内存中。  
  
- DataManage.h/DataManage.cpp：  
  管理游戏的DMS数据。  
  
- main.cpp：  
  游戏主函数，包含了游戏的主循环。  
  
## 版权声明：  
- 本项目基于raylib图形库实现，其版权归原作者所有。  
  
> 如有任何疑问，请联系作者：<ma200511@qq.com>  
> 项目地址：https://github.com/qinmoM/SG-Engine2D  
> 欢迎讨论。  