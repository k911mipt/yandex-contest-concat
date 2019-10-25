# yandex-contest-concat

Simple c++ preprocessor for **Yandex Contest**

## Problem

Yandex contest only eats single '.cpp' files for submits. But when you develop project, most people prefer split into few files.
If we use standard c++ preprocessor output, it will include all mentioned headers, like

```c++
#include <iostream>
```

Our single file will become **huge** and **Yandex Contest** won't take it.

So usually we only want to inlude *our* files, like

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

Sample inluded: `yandex-contest-concat.exe test.cpp out.cpp`

As for now this tool does not perform circularity checks and multiincluding checks. So you must guard all your `.h` files like this

```c++
#ifndef TEST_H_
#define TEST_H_


int test();

#endif // TEST_H_
```

## TODO

* [ ] Prevent multiincluding
* [ ] `make`, `make install`, `make unistall`
* [ ] Relative paths handling

___

## Good luck and have fun! :-)
