# patchqtcore

This tool is based on single feature from [windeployqt](http://doc.qt.io/qt-5/windows-deployment.html) and allows to remove hard-coded Qt prefix path. *patchqtcore* doesn't create any backup and shouldn't be used in Qt installation folder. To use starts the tool with *Qt5Core.dll* or *Qt5Cored.dll* as single argument. Pointed file will be modified. As usual silent is means success.

Binary file actually named *pachqtcore* due [UAC feature](https://answers.microsoft.com/en-us/windows/forum/windows_7-security/uac-prompts-on-any-program-with-the-word-patch-or/c5359497-d16e-43c6-99f2-db3d8eecc9c0). It's not a typo.
