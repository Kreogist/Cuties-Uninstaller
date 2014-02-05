Cuties Uninstaller
==================
Cuties Uninstaller is an application to uninstall Cuties especially for Microsoft Windows Platform.

The reason why we only write an uninstaller for Windows is that Mac OS X and Linux is so powerful that they don't need such a tool like this.

## Building Prerequisites

Cuties Uninstaller requires that various tools and packages be available for use in the build procedure. Modifying Cuties Uninstaller sources requires additional tools described below.

If you think the following step is too advanced or too tedious, we provide you a [Quick preparing guide](https://github.com/Kreogist/Cuties/wiki/Quick-preparing-guide). And you can skip to Downloading the source.

### Tools/packages necessary for building Cuties Uninstaller

* **Qt 5.1.1 libraries or above**

You should have 5.1.1 or later version of Qt. We suggest you to use Qt 5.2 to build Cuties Uninstaller.

Please **DO NOT** use Qt 5.1, there're several bugs in Qt 5.1 and it works really bad on Mac OS X. We are not sure whether it has bugs on Winodws. Use Qt 5.1.1 instead , it works really nice.

If you have trouble with set up Qt, please visit [Download Qt](http://qt-project.org/downloads) for binary packages, [Getting Started with Qt](http://qt-project.org/doc/qt-5/gettingstarted.html) for Downloading and Installing Qt guide.

* **Compiler**

We suggest you to use MinGW GNU Compiler Collections (MinGW GCC). You can get it from the [homepage](http://gcc.gnu.org/) of GCC. If you hope that you don't have to worry about the compilers, we suggest you to download binary package 'Qt 5.2.0 for Windows 32-bit' on Qt Project [download page](http://qt-project.org/downloads).

### Tools/packages additional for building Cuties Uninstaller

* **Qt Creator 2.7 or above**

You may need a Qt Creator to do make and build for you instead of doing them by yourself. We suggest you to build Cuties Uninstaller with Qt Creator.

For Qt 5.1.1, we suggest you to use Qt Creator 2.7.2. For Qt 5.2, we suggest you to use Qt Creator 3.0. For more details about Qt Creator, please visit [Qt Project](http://qt-project.org/).

* **CMake**

We are know currently working on build Cuties Uninstaller for CMake. You can use CMake instead of qmake to build Cuties Uninstaller if you like to.

### Tools/packages necessary for modifying Cuties Uninstaller

* **A code editor or an IDE**

To modifying Cuties Uninstaller code, you should have a code editor - like Notepad in Windows, though we all don't like to use it :) - or an IDE - like Qt Creator.

So, we really suggest you to download the full package of Qt 5.1.1 or above. You can find Qt Creator and Qt Linguist on http://qt-project.org. We suggest you to download a binary package which includes Qt libraries and Qt Creator from http://qt-project.org/downloads.

### Tips from Kreogist
* **The version of Qt we used to build Cuties Uninstaller**

We build Cuties on Windows Platform via Qt 5.2.0 for Android (Windows 32-bit, 761 MB).

* **Set environment variables**
Please add the path of Qt to your system environment variables %PATH%. It should be like a path below:

    D:\Qt\Qt5.2.0\5.2.0\mingw48_32\bin

And you have to add MinGW compiler path to your system environment variables %PATH%. To learn more about system environment varibables, please visit [Environment variable](http://en.wikipedia.org/wiki/Environment_variable#Microsoft_Windows) on Wikipedia. To learn more about how to set system environment variable on Windows, please visit [User Environment Variables](http://msdn.microsoft.com/en-us/library/windows/desktop/bb776899%28v=vs.85%29.aspx) from Microsoft Dev Center - Desktop.

## Downloading the source

Cuties Uninstaller is distributed via Git and HTTP tarballs compressed with zip or tar.gz.

You can download our source code from the right bottom of the [project homepage](https://github.com/Kreogist/Cuties-Uninstaller) of Cuties Uninstaller. Or if you like to, here we provide the four links to download the package directly:

* [Cuties Uninstaller source code tar.gz package(master)](https://github.com/Kreogist/Cuties-Uninstaller/tarball/master): tar.gz format source code package of branch master. 
* [Cuties Uninstaller source code zip package(master)](https://github.com/Kreogist/Cuties-Uninstaller/zipball/master): zip format source code package of branch master. 
* [Cuties Uninstaller source code tar.gz package(dev)](https://github.com/Kreogist/Cuties-Uninstaller/tarball/dev): tar.gz format source code package of branch dev. 
* [Cuties Uninstaller source code zip package(dev)](https://github.com/Kreogist/Cuties-Uninstaller/zipball/dev): zip format source code package of branch dev. 

You can also get the source code by cloning the git repository. For more information about Git and Manage your code, please visit [Git, managed code](https://github.com/Kreogist/Cuties/wiki/Git,-managed-code).

## Building

Here we will use Qt Creator to build Cuties Uninstaller. We will show you how to build Cuties Uninstaller in Windows platform. It is nearly the same as what it will be in Mac OS X and Linux.

Launch Qt Creator and open the `Cuties-Uninstaller.pro` in `src` folder. 

Choose Build > Build Project or press Ctrl+B to build Cuties. Wait for it finished.

Open your build directory in your file browser. You will find several folders and files:

	debug                  <Directory>
	release                <Directory>
	Makefile               <File>
	Makefile.Debug         <File>
	Makefile.Release       <File>

Open release folder, you will find a binary file `Cuties-Uninstaller.exe`. The copy the following files to the directory `(You build directory)/release`:

International Components for Unicode(ICU) Libraries:

    icudt51.dll
    icuin51.dll
    icuuc51.dll

For MinGW compiler, C/C++ runtime libraries.

    libgcc_s_dw2-1.dll
    libstdc++-6.dll
    libwinpthread-1.dll

Qt 5 Libraries:

    Qt5Core.dll
    Qt5Gui.dll
    Qt5Multimedia.dll
    Qt5Widgets.dll

Now, try to launch Cuties-Uninstaller.exe, It should can be used.