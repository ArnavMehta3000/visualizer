# Visualizer

Tool for loading and testing transpiled shader files.
- Metal Shaders
- GLSL Shaders
- HLSL Shaders

# Project Structure

The project is divided into two sub projects

- **VisualizerCore**: Static library that contains the core functionality
- **VisualizerApp**: Contains the platform independent GUI application that depends on the Core

# Building The Project

To build the project ensure you have the following toolsets

- [Xmake](https://xmake.io/)
- C++23 compiler

## External Dependencies

- SDL2
- NCurses (linux/mac only)

</br>

## Clone the repository

```
git clone https://github.com/CrossGL/visualizer.git
```

## Load Build Macros

The repo comes with a couple helper xmake macros. Load these macros by running the [LoadMacros.bat](./LoadMacros.bat) file. **You only need to run this bat script only once, or if you delete the generated *`.xmake`* folder**.

After running the script the following macros will be imported (case insensitive):

- **BuildAllConfigs**: Builds the visualizer for both debug and release configurations
- **Clean**: Cleans the xmake configs and targets
- **DeepClean**: Similar to the *Clean* macro but also deletes the build folder
- **GenVS**: Generates Visual Studio 2022 solution files
- **GenXC**: Generates XCode project files

You can run these above macros using the following command

```bash
xmake macro <macro name>
```

## Choosing The Build Configuration

Before compiling the project you can also set the build config

To make use of the debug config

```bash
xmake f -m debug
```

To make use of the release config

```bash
xmake f -m release
```

## Compiling The Project

### Using The Macros

Build all the configs

```bash
xmake macro buildallconfigs
```

### Compiling Using Visual Studio

Generate VS 2022 files

```bash
xmake macro genvs
```

This will generate the solution files in the vsxmake2022 folder

### Compiling Using CMake

Generate CMakeLists.txt

```bash
xmake project -k cmakelists
```

This will generate the CMakeLists.txt in the root folder


# Contributing

When contributing to the project. Ensure the project passes the compilation test locally on your PC.

```bash
xmake test
```

The expected output should be such that all project compile and link successfully
