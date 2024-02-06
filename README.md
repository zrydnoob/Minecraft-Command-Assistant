# Minecraft-Command-Assistant
## 背景
在我发现OpenGL ImGui打包为动态链接库被注入到Minecraft中,并且可以在Minecraft中显示ImGui界面后,我计划制作一个命令助手注入到游戏中方便我的游戏

## 支持的游戏版本
目前在1.14+

## 功能
与MC百科的[命令生成器](https://www.mcmod.cn/tools/cbcreator/)功能相同,能够生成基础命令 物品给予 NBT标签 json相关等命令

## 安装
想要在游戏中使用它:
1. 下载Releases中的.dll文件
2. 运行Minecraft游戏
3. 使用dll的注入器将下载的文件注入到Minecraft的游戏进程中
4. 在游戏中按下键盘上的Insert键打开菜单

注意:本项目仅供学习使用，不提供任何注入器，请勿用于其他用途

## 注意事项
分支main是注入版本源码

分支develop是开发调试的窗口版本

在构建过程中请注意所下载的分支

#### 今后开发过程中我将先使用develop分支开发,待基础功能完成后移植到注入版中
#### 本项目的开发还未完成 高中没有太长的时间和精力投入开发 开发计划可能会无限期搁置
此仓库暂仅用于代码托管，不发布release

## 构建
想要自己构建并生成dll文件
1. 请下载[Visual Studio](https://visualstudio.microsoft.com/zh-hans/vs/)
2. 在安装器中选择社区版Visual Studio 2022
3. 在弹出的页面选择 使用C++的桌面开发
4. 打开项目 生成即可

## 使用
注入版使用C++语言 Opengl ImGui进行开发

带窗口的版本是为了方便开发调试，使用了ImGui glew glfw

本项目的功能和布局照搬了 MC模组百科的[命令生成器](https://www.mcmod.cn/tools/cbcreator/)
