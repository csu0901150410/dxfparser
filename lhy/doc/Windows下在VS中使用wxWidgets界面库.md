第一步：下载并编译`wxWidgets`。

到`wxWidgets`官网（[https://www.wxwidgets.org/downloads/](https://www.wxwidgets.org/downloads/)）下载源码包到本地。

![下载源码包](Images/Windows%E4%B8%8B%E5%9C%A8VS%E4%B8%AD%E4%BD%BF%E7%94%A8wxWidgets%E7%95%8C%E9%9D%A2%E5%BA%93/20231204001.png)

解压源码包，比方说解压到`wxWidgets`目录下，定位到路径`wxWidgets\build\msw\`下的`wx_vcxx.sln`，这是一个`Visual Studio`解决方案文件，打开它。

查看一下路径`wxWidgets\lib\`的文件，稍后编译产生的`.lib`和`.dll`文件将会放到此路径下。

切换到打开的`wx_vcxx.sln`解决方案，选择`生成`选项卡下的`批生成`，点击全选然后点击生成，等待生成完毕。如果失败，则重新生成。

![编译库](Images/Windows%E4%B8%8B%E5%9C%A8VS%E4%B8%AD%E4%BD%BF%E7%94%A8wxWidgets%E7%95%8C%E9%9D%A2%E5%BA%93/20231204002.png)

生成结束后检查路径`wxWidgets\lib\`，确认库文件已生成。

![库文件](Images/Windows%E4%B8%8B%E5%9C%A8VS%E4%B8%AD%E4%BD%BF%E7%94%A8wxWidgets%E7%95%8C%E9%9D%A2%E5%BA%93/20231204003.png)

第二步：编写测试程序

在VS中新建空项目，添加一个`main.cpp`源文件，在其中粘贴如下代码。

```cpp
#include <wx/wx.h>

class App : public wxApp {
public:
    bool OnInit() {
        wxFrame* window = new wxFrame(NULL, wxID_ANY, "Windows Title", wxDefaultPosition, wxSize(600, 400));
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* text = new wxStaticText(window, wxID_ANY, "Hello, World!",
            wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
        text->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        sizer->Add(text, 1, wxALIGN_CENTER);
        window->SetSizer(sizer);
        window->Show();
        return true;
    }
};

wxIMPLEMENT_APP(App);
```

`Ctrl+Shift+B`，当然是报错的。我们还需要将`wxWidgets`库的头文件和库文件配置到项目中。

首先，将编译之后的`wxWidgets`文件夹路径加入系统环境变量，比如我这里将`wxWidgets`路径设为`ENV_wxWidgets`。

![环境变量](Images/Windows%E4%B8%8B%E5%9C%A8VS%E4%B8%AD%E4%BD%BF%E7%94%A8wxWidgets%E7%95%8C%E9%9D%A2%E5%BA%93/20231204004.png)

然后，在VS中右键项目选择属性打开属性页，改三个地方。
- 属性页`C/C++`下`常规`中的`附加包含目录`，填入值`$(ENV_wxWidgets)\include;$(ENV_wxWidgets)\include\msvc;`，这里的`$(ENV_wxWidgets)`就是取环境变量`ENV_wxWidgets`的路径，取到的自然就是`wxWidgets`源码解压的路径，再拼接上后续的字符串，就指定了附加包含目录为源码目录下的`include`和`include/msvc`文件夹。
- 属性页`链接器`下`常规`中的`附加库目录`，填入值`$(ENV_wxWidgets)\lib\vc_x64_lib`。注意，如果是平台是32位的，需要填入`$(ENV_wxWidgets)\lib\vc_lib`。如下图所示，如果生成出错，不妨检查下当前所选配置以及平台是否设置了正确的属性。
- 属性页`链接器`下`系统`中的`子系统`，选择窗口。

![属性页](Images/Windows%E4%B8%8B%E5%9C%A8VS%E4%B8%AD%E4%BD%BF%E7%94%A8wxWidgets%E7%95%8C%E9%9D%A2%E5%BA%93/20231204005.png)

至此，再`Ctrl+Shift+B`接着`F5`走一波，程序就跑起来了。

![成功运行](Images/Windows%E4%B8%8B%E5%9C%A8VS%E4%B8%AD%E4%BD%BF%E7%94%A8wxWidgets%E7%95%8C%E9%9D%A2%E5%BA%93/20231204006.png)

现在就拥有界面工具了。