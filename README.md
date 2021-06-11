# CuteStation

![C/C++ CI](https://github.com/ngc7293/cutestation/workflows/C/C++%20CI/badge.svg)

## Contents

- [CuteStation](#cutestation)
  - [Contents](#contents)
  - [Goals](#goals)
  - [Structure](#structure)
  - [Depends](#depends)
  - [Building](#building)
  - [Testing](#testing)

## Goals

CuteStation is a Qt-based ground control system.

The goal with this project is to create a native Qt-based application to display
telemetry data. To maximise reusability, data is received via Google's Protobuf.
This means that in most cases, you will need two applications: CuteStation and a
converter to transform your devices' protocol into Protobuf, but will save on
writing all that data handling and UI code.

The GUI itself aims to be ultra-configurable with various widget you could match
to different data sources, and layout to your desires. Think of it as a native
Grafana that does not rely on an external database.

Daemons (the processes pushing data to CuteStation) can also register Commands
which are matched to UI controls. This enables you to send back commands from
CuteStation's UI.

Note that this is also an excuse for me to try and improve my knowledge of
modern C++ syntax and practices. I've therefore sometimes decided to reinvent
the wheel and use custom implementation of already available modules. Most
notably you'll find that `net` could easily be removed and replaced with Qt's
Network stack, but then I wouldn't have had the chance to look into the workings
of socket programming on Linux and the inners of iostreams.

## Structure

The project is split in several smaller static libraries defined in CMakeFiles.
This approach was chosen because I believe it helps designing cleaner, more
reusable modules by defining clear boundaries. Each (most) libraries come with
a Google Test-driven unit test executable named `<target>.test` (e.g.:
`cute.io.test`).

| Module        | Description
|:--------------|:--------------------------------------------------------------
| `net`         | Socket communication using iostreams. Currently only works for Unix and TCP sockets on Unix.
| `topic`       | Topic-based publish-subscribe system. Should be thread-safe, but makes no attempt at multi-threading optimization, that is left to the user.
| `cute.io`     | Handles IPC with external data sources for CuteStation.
| `cute.data`   | Containers for real-time data.
| `cute.widgets`| Widgets to display real-time data (contained in cute.data containers)
| `cute`        | The actual application (main, App(), etc.)

## Depends

- Conan
- CMake 3.17 (for [CMP0100](https://cmake.org/cmake/help/v3.17/policy/CMP0100.html))
- Ninja (recommended)

CuteStation uses C++20 features and syntax; a modern compiler is required. The
officially supported compiler is GCC 9.3.0.

## Building

To clone:

```bash
git clone https://github.com/ngc7293/cutestation
cd cutestation
```

To build

```bash
mkdir build; cd build;
conan install .. -s compiler.libcxx=libstdc++11 -s cppstd=20 -s build_type=Debug --build=missing
cmake .. -G Ninja
ninja
```

## Testing

Most modules have unit tests. These are built with Google Test into one
executable per module, using the syntax `<module>.test`. They can be found in
the `build/bin` directory.

**Coverage is currently disabled. We'll be back soon.**

After running tests, you can generate the coverage report with `ninja coverage`.
Detailed coverage information will be written to `build/coverage.html`.

**Note**: Linux will purposefully keep TCP sockets alive for a certain time
after they are closed. This will cause the TCP Server tests to fail if called
repeatedly. These failures can be ignored (the tests are DISABLED in gtest)
