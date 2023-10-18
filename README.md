# DXF解析实现-dxfparser

DXF是AutoCAD的绘图交换文件，可以理解为一种描述图形的文本文件。大致介绍见[DXF 百度百科](https://baike.baidu.com/item/DXF/364192)。

有条件的可以参考[DXF 维基百科](https://en.wikipedia.org/wiki/AutoCAD_DXF)，文末附有PDF格式的DXF格式说明文档。

> 以下两个链接分别是DXF格式的规格手册和参考手册
> 1、[https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf](https://images.autodesk.com/adsk/files/autocad_2012_pdf_dxf-reference_enu.pdf)
> 2、[http://docs.autodesk.com/ACD/2011/CHS/filesDXF/WSfacf1429558a55de185c428100849a0ab7-5f35.htm](http://docs.autodesk.com/ACD/2011/CHS/filesDXF/WSfacf1429558a55de185c428100849a0ab7-5f35.htm)

### 目标

- 使用C/C++实现DXF文件的解析；
- 实现一个图形化界面用于显示从DXF文件中解析的图形，方便开发过程中验证；
- 实现一个简单的表示图形的函数库，方便表示从DXF中解析的图形；

### 准备工作

- 代码编辑器VSCode；
- Visual Studio；
- **AutoCAD，用于绘图导出DXF文件**，主要是这一项；
- 其他开发过程中使用到的工具；

### 阶段性目标

- 1、能够读入DXF文本文件，解析其中的实体信息，包括基础的点、线、圆的坐标信息，输出至控制台；
- 2、构建简单的点、线、圆等图元的结构体，用以描述从DXF中解析出来的实体信息；
- 3、实现简单的图形化界面，能够在屏幕显示点、线、圆等图形；
- 4、迭代完善DXF解析、图形库、界面库。

### 备忘录

- 使用GDI图形绘制构建界面，参考链接：[GDI+入门](https://learn.microsoft.com/zh-cn/windows/win32/gdiplus/-gdiplus-getting-started-use)。