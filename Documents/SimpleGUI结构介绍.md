SimpleGUI 结构介绍
---
## 1. 概述 

&emsp;&emsp;本文将详细介绍SimpleGUI各个机能模块的组成与依赖关系，方便用户根据自己的具体需求对SimpleGUI进行必要的剪裁，以实现资源消耗的最小化。  
&emsp;&emsp;SimpleGUI分为GUI和HMI两部分，GUI部分负责显示和绘图控制，HMI则提供了一种构件和管理界面的逻辑关系的手段，方便开发者分离业务逻辑和画面显示，更有利于编写和维护。如果不需要，HMI可不使用。

## 2. GUI部分

### 2.1. 基本数据类型  
&emsp;&emsp;为避免在因不同平台、不同编译器下对不同基本数据类型的定义不同导致的可能潜在的问题，SimpleGUI单独使用了一个名为SGUI_Typedef.h的文件，对SimpleGUI的数据类型进行了重新封装，以避免因为不同数据类型的表达范围、指针等问题导致难以调查的系统异常。

### 2.2. 设备驱动
&emsp;&emsp;在使用SimpleGUI之前，首先需要您实现您目标平台上对屏幕设备的操作函数。实现内容至少为：
|函数功能|参数表|返回值|  
|:--|:--|:--|  
|读取屏幕像素点|SGUI_INT iX, SGUI_INT iY|SGUI_INT|  
|设定(写入)屏幕像素点|SGUI_INT iX, SGUI_INT iY, SGUI_INT iColor|void|  

&emsp;&emsp;如果不考虑执行效率，以上两个函数实现后就，SimpleGUi就可以工作了，当然，如果想更有效的绘图，还需根据驱动程序的逻辑结构、缓存的数据结构、硬件特性等因素实现其他的接口函数，如清除屏幕、更新屏幕、水平线绘制、垂直线绘制等。  

&emsp;&emsp;SimpleGUI对显示设备的操作是通过一个名为SGUI_SCR_DEV(SimpleGUI Screen Device)的结构体实例来实现的，结构体的定义为：  

```c++
typedef struct
{
    //Engine & device initialize function.
    SGUI_ENGINE_ACTION_FN_INITIALIZE	        fnInitialize;
    //Clear screen function.
    SGUI_ENGINE_ACTION_FN_CLEAR                 fnClearScreen;
    //Set pixel value function.
    SGUI_ENGINE_ACTION_FN_SET_POINT             fnSetPixel;
    //Get pixel value function.
    SGUI_ENGINE_ACTION_FN_GET_POINT             fnGetPixel;
    // Refresh screen display.
    SGUI_ENGINE_ACTION_FN_REFRESH               fnRefreshScreen;
}SGUI_SCR_DEV;
```
&emsp;&emsp;此数据结构的定义位于SGUI_Typedef.h文件中，包含若干函数指针，用户需要声明一个此类型的结构体，然后按照结构体中函数指针的数据类型设计和实现相应功能的设备驱动函数，并将对应的函数指针注册到结构体实例，然后在调用SimpleGUI绘图函数时，将该结构体的指针作为参数传入函数（通常是参数表的第一个参数）。  

&emsp;&emsp;除前文描述的像素点读写函数外，SGUI_SCR_DEV结构体中的其他函数通常只有在需要实现显示缓存时才可能用到，描述如下：
|指针|函数功能|参数表|返回值|  
|:--|:--|:--|:--|  
|fnInitialize|设备初始化，通常由HMI部分调用。|void|SGUI_INT|  
|fnClearScreen|清除屏幕显示，如果使用了显示缓存，同时清除缓存。|void|void|  
|fnRefreshScreen|更新屏幕显示，通常指将显示缓存的数据同步到设备。|void|void|  


&emsp;&emsp;其他具体的数据类型定义请参考SGUI_Typedef.h文件的内容。

### 2.3. 逻辑结构

&emsp;&emsp;SimpleGUI的所有接口有着明确的包含关系，可以简单的划分为“平台接口”、“共通机能”、“基础绘图”和“控件”四部分。  

#### &emsp;&emsp;平台接口  
&emsp;&emsp;此部分接口的实现位于SGUI_Interface.c文件中，封装或实现包括内存块复制(memcpy)、赋值(memset)、申请与释放(malloc/free)字符串的复制(strcpy/strncpy)、长度测量(strlen)以及当前时间(RTC时间)的获取、Flash(包括内部和外部)中数据的获取等依赖于系统平台的机能实现。  
#### &emsp;&emsp;共通机能
&emsp;&emsp;此部分接口的实现位于SGUI_Common.c文件中，封装或实现了包括数字与字符串之间的格式化转换、以及小数点的插入等。由于SimpleGUI中全程避免使用浮点数，所以小数点基本上都是通过格式化字符串得来，请悉知。  
#### &emsp;&emsp;基础绘图
&emsp;&emsp;此部分接口的实现位于SGUI_Basic.c文件中，封装或实现了点、线、圆形、矩形以及位图的绘制，以及区域反色、屏幕内容的更新(仅在使用显示缓存时有用)与清除等。  
#### &emsp;&emsp;控件
&emsp;&emsp;此部分也可被称为“组件”，实现于多个文件中，提供了多种方便使用的接口组。  

|文件名|功能概要|    
|:--|:-- |  
|SGUI_Text.c|提供封装好的文字绘制接口、包括单行、多行以及绘制文字前需要的部分预演算等。|   
|SGUI_Frame.c|边框绘制接口，用于绘制屏幕边框，例如列表和实时曲线的窗口边框等。|  
|SGUI_Notice.c|用于显示一个消息提示框，提示一些文字内容，可带图标，类似Windows中的MessageBox。|  
|SGUI_ScrollBar.c|提供显示水平或垂直滚动条的接口。|   
|SGUI_ProcessBar.c|提供进度条的显示接口，支持上、下、左、右四个生长方向。|   
|SGUI_List|提供列表显示接口，可以显示一个列表，列表项目可以为枚举字符串型、整数型、小数型或不带参数的普通型。|  
|SGUI_VariableBox.c|提供数值输入和字符串输入两种输入框接口。|  
|SGUI_RealtimeGraph.c|提供封装好的实时曲线界面接口，可以在屏幕上根据用户输入的点数据绘制和现实一条实时曲线。|  

&emsp;&emsp;以上文件均提供同名的头文件(.h)，可以直接包含和调用。 

&emsp;&emsp;所有的控件的实例在显示和操作中，均使用一个结构体进行数据和参数的保存，同时，所有的控件均提供画面更新接口(SGUI_XXX_Refresh函数)，用以在任何需要的时候恢复控件在屏幕设备上的显示。此方法的设计意在在绝大多数情况下可以取代图层的概念。

### 2.4. 依赖关系  

&emsp;&emsp;SimpleGUI为了可以在一定程度上实现剪裁，将代码设计为前文描述的四部分，四部分从高到低，大体呈依赖关系，例如控件的实现依赖基础绘图、基础绘图的实现依赖共通机能、共通机能的实现一定程度上依赖平台接口。  
&emsp;&emsp;以最常用的列表为例，列表的实现、依赖Frame、ScrollBar两个控件、Text中的文本绘制功能、同时还依赖基础绘图的区域反色功能。  
&emsp;&emsp;


## 3. HMI模型
