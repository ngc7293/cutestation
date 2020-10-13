# CuteStation

Contents

- [Goals](#Goals)
- [Structure](#Structure)
- [Depends](#Depends)
- [Building](#Building)
- [Testing](#Testing)

## Goals

CuteStation is a Qt-based ground control system.

The goal with this project is to create a native Qt-based application to display
telemetry data. To maximise reusability, data is received via Google's Protobuf.
This means that in most cases, you will need two applications: CuteStation and a
converter to transform your devices' protocol into Protobuf, but will save on
writing all that data handling and UI code.

The GUI itself aims to be ultra-configurable with various widget you could match
to different data sources, and layout to your desires. Think of it as a native
Grafana that does not rely on a database.

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

- `net` : Socket communication using iostreams. Currently only works for Unix
          and TCP sockets on Unix.
- `topic` : Topic-based publish-subscribe system. Should be thread-safe,
            but makes no attempt at multi-threading optimization, that is
            left to the user.
- `cute.io` : Handles IPC with external data sources for CuteStation.

## Depends

- [Protobuf 3.11](https://github.com/protocolbuffers/protobuf/)
- [nlohmann::json](https://github.com/nlohmann/json)
- Qt 5.14.1
- CMake 3.17
- Ninja (recommended)
- gcovr (recommended)

On Ubuntu, all of these except Qt5 can be installed from the repositories. Qt5's
installer can be found on their website. I recommend installing in `/opt/Qt`.

Alternatively, you might want to install Protobuf from source. The process is
quite simple can be found [here](https://github.com/protocolbuffers/protobuf/blob/master/src/README.md).
This is likely to be necessary in the future to ensure a speficic, stable
version is used.

CuteStation uses C++20 features and syntax; a modern compiler is required.

## Building

```bash
mkdir build; cd build;
cmake .. -G Ninja
ninja
```

Clazy is not technically required for the project to work, but all code written for this project is expected to compile without warnings from clang or clazy.

Note that the current CMakeLists assumes Qt to be installed in
`/opt/Qt/5.14.1/`, you might need to update it to match your install path.

## Testing

There are currently 3 test executables : `cute.io.test`, `topic.test` and
`net.test`. All output binaries can be found in `build/bin`.

After running tests, you can generate the coverage report with `ninja coverage`.
Detailed coverage information will be written to `build/coverage.html`.

**Note**: Linux will purposefully keep TCP sockets alive for a certain time
after they are closed. This will cause the TCP Server tests to fail if called
repeatedly. These failures can be ignored.
