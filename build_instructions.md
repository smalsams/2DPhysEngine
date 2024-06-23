### Prerequisites for building on all platforms:

* CMake 3.16 or higher
* C++ compiler with C++17 support
* Be in the project serafins/project directory

# Windows Build

* use CMake to build the project:
```
cmake -S . -B build
cmake --build build --config Release
```

# Linux Build

## Prerequisites

You will need to install the following packages (if on Ubuntu or other Debian based distribution):

```bash
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
```

## Building

* use CMake to build the project:
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

-----------------------------------------------------------------
After this, you will find the executable in the `./build/bin` on Linux and './build/bin/Release' on Windows. 