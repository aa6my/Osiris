# Osiris

![Windows](https://github.com/danielkrupinski/Osiris/workflows/Windows/badge.svg?branch=master&event=push)
![Linux](https://github.com/danielkrupinski/Osiris/workflows/Linux/badge.svg?branch=master&event=push)

Free and open-source game hack for **Counter-Strike 2**. Compatible with the latest Steam version of the game. Cross-platform - available for Windows and Linux systems.

## What's new

* 23 November 2023 - **Visualize Bomb Defuse** function was added to **Sound**
* 16 November 2023 - **Visualize Bomb Beep** function was added to **Sound**
* 8 November 2023 - Adjusted positions of sound visualizations to be closer to the sound source
* 1 November 2023 - **Visualize Bomb Plant** function was added to **Sound**
* 27 October 2023 - **Visualize Player Footsteps** function was added to **Sound**

## Technical features

* C++ runtime library (CRT) is not used in release builds
* No heap memory allocations
* No static imports in release build on Windows
* No threads are created
* Exceptions are not used
* No external dependencies

## Compiling

### Prerequisites

#### Windows

* **Microsoft Visual Studio 2022** with **Desktop development with C++** workload

or
* **CMake 3.24** or **newer**
* **MSVC 19** or **newer**

#### Linux

* **CMake 3.24** or **newer**
* **g++ 11 or newer** or **clang++ 15 or newer**

### Compiling from source

#### Windows

Configure with Visual Studio 2022:
Open **Osiris.sln**, set build configuration to **Release | x64**. Press *Build solution* and you should receive **Osiris.dll** file.

or

Configure with CMake & Build:

`cmd`

    rmdir /s /q build && cmake -DCMAKE_BUILD_TYPE=Release -B build && cmake --build build/ -j %NUMBER_OF_PROCESSORS%

`powershell`

    rm -r -fo build && cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build/ -j $env:NUMBER_OF_PROCESSORS

#### Linux

Configure with CMake & Build:

    rm -rf build && cmake -DCMAKE_BUILD_TYPE=Release -B build && cmake --build build -j $(nproc --all)

After following these steps you should receive **libOsiris.so** file in **build/Source/** directory.

### Loading / Injecting into game process

#### Windows

You need a **DLL injector** to inject (load) **Osiris.dll** into game process.

Counter-Strike 2 blocks LoadLibrary injection method, so you have to use a manual mapping (aka reflective DLL injection) injector.

**Xenos** and **Extreme Injector** are known to be **detected** by VAC.

#### Linux

You can simply run the following script in the directory containing **libOsiris.so**:

    sudo gdb -batch-silent -p $(pidof cs2) -ex "call (void*)dlopen(\"$PWD/libOsiris.so\", 2)"

However, this injection method might be detected by VAC as gdb is visible under **TracerPid** in `/proc/$(pidof cs2)/status` for the duration of the injection.

## License

> Copyright (c) 2018-2023 Daniel Krupiński

This project is licensed under the [MIT License](https://opensource.org/licenses/mit-license.php) - see the [LICENSE](https://github.com/danielkrupinski/Osiris/blob/master/LICENSE) file for details.
