# yandex-contest-concat

Simple c++ preprocessor for [**Yandex Contest**](https://contest.yandex.ru/contest)

## Problem

Yandex contest only eats single '.cpp' files for submits. But when you develop project, most people prefer split into few files.
If we use standard c++ preprocessor output, it will include all mentioned headers, like

```c++
#include <iostream>
```

Our single file will become **huge** and **Yandex Contest** won't take it.

So usually we only want to include *our* files, like

```c++
#include "some_file.h"
```

## Solution

So i wrote a little tool, which can help you concat that project into one file.

This tool only supports project with this requirments:

* **One** `.cpp` file
* Multiple `.h`, `.hpp` or whatever extension you want files, included with pattern `#include "file_name"`
* All file must be placed in one folder and it must be same folder, where binary is located

Usage:

```cmd
yandex-contest-concat.exe input_file output_file
```

Sample included: `yandex-contest-concat.exe test.cpp out.cpp`

included files are bordered with regions

```c++
#pragma region "file_name.h"
// body
#pragma endregion "file_name.h"
```

This tool **will not** include same file twice, ~~so you don't need to care about guarding headers~~ you still must always care about guarding headers anyway

```c++
#ifndef FILENAME_H_
#define FILENAME_H_
// body
#endif // FILENAME_H_
```

## TODO

* [ ] Relative paths handling

___

## Good luck and have fun! :-)
