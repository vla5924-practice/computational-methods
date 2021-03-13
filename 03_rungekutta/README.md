# Lab 3. Differential equations system solver with Runge-Kutta method

Implement differential equations system solver with Runge-Kutta method.

## Software stack

C++11, Qt 5.15, MSVC (for Windows).

## Deployment manual

1. Compile project with _Release_ configuration.
2. Create empty folder for deployment and copy compiled `03_rungekutta.exe` file there.
3. Run _windeployqt_ (located in _bin_ folder of your Qt installation) from deployment folder passing executable filename as first argument. Example:
   ```sh
   "A:\libraries\Qt\5.15.1\msvc2019_64\bin\windeployqt.exe" 03_rungekutta.exe
   ```
4. After _windeployqt_ application finishes copying the necessary files to your folder, leave only the following files and folders there (and delete the rest):
   * `03_rungekutta.exe`
   * `platforms`
   * `styles`
   * `Qt5Core.dll`
   * `Qt5Gui.dll`
   * `Qt5Svg.dll`
   * `Qt5Widgets.dll`
5. Also copy shared runtime library of your compiler if needed (for example, `vcruntime140_1.dll` for latest version of MSVC could be found in _bin_ folder in this repository).
6. Rename `03_rungekutta.exe` executable to any name you want (if necessary).
