# Configuration and building
The project is ran and tested on windows and using Visual Studio Code.

In order to configure and build the project in VSCode, some settings must be set either globally (as in the case of my configuration), or in the project.

## 1. CMake Tools plugin
The "CMake Tools" extension and the CMake language support extension is used on my environment.
A kit must be configured for the CMake Tools extension at `C:\Users\your_user_name\AppData\Local\CMakeTools\cmake-tools-kits.json`

Mine looks like this:
```json
[
  {
    "name": "MSYS2 UCRT64 with Ninja",
    "compilers": {
      "C":"C:\\msys64\\ucrt64\\bin\\gcc.exe",
      "CXX":"C:\\msys64\\ucrt64\\bin\\g++.exe"
    },
    "isTrusted": true,
    "preferredGenerator":{
      "name":"Ninja"
    }
  }
]
```

I'm using msys2 and withing that the ucrt64 environment for comiling the project and also for building its dependencies from source.

## 2. Settings
In the user scoped settings JSON the following values are set:
```json
    "cmake.cmakePath": "C:/msys64/ucrt64/bin/cmake.exe",
    "cmake.configureSettings": {
        "CMAKE_MAKE_PROGRAM": "C:/msys64/ucrt64/bin/ninja.exe"
    }
```

## 3. Configuration file
The `CMakeLists.txt` also expects a configuration file named `Config.cmake` in the direct parent directory of the project.
This is used to set the paths to installed dependencies.
```CMake
set(WX_WIDGET_INSTALL_ROOT "C:/path/to/my/wxWidgets/build/wxWidgets-3.2.4")
set(MSYS2_UCRT64_ROOT "C:/msys64/ucrt64")
```