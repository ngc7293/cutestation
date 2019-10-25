# CuteStation

## Goal

CuteStation is a Qt-based ground control system.

The goal with this project is to create a native Qt-based application to display telemetry data. To maximise reusability, data is received via Google's Protobuf. This means that in most cases, you will need two applications: CuteStation and a converter to transform your devices' protocol into Protobuf, but will save on writing all that data handling and UI code.

The GUI itself aims to be ultra-configurable with various widget you could match to different data sources, and layout to your desires. Think of it as a native Grafana that does not rely on a database.

Daemons (the processes pushing data to CuteStation) can also register Commands which are matched to UI controls. This enables you to send back commands from CuteStation's UI.

## Depends

- Protobuf 3.10
- Qt 5.12.1
- CMake
- Ninja (recommended)

## Building

```bash
mkdir build; cd build;
cmake .. -G Ninja
ninja
```

Note that the current CMakeLists assumes Qt to be installed in `/opt/Qt/5.12.1/`, you might need to update it to match your install path.

To rebuild Protobuf classes after you changed them:

```bash
protoc proto/ --cpp_out src/
mv src/proto/*.h inc/proto
```
