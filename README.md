# CuteStation

CuteStation is a Qt-based telemetry monitoring program.

My goals with this project is to create a native Qt-based application to display and log telemetry data. To maximise reusability, data would be received via a (custom) JSON protocol. You would therefore, in most cases, need two applications: CuteStation and a converter to transform your devices' protocol into JSON.

The GUI itself would aim to be ultra-configurable with various widget you could match to different data sources, and layout to your desires. Think of a native Grafana that does not rely on a database. Eventually, I'd interested in adding the ability to send commands to your devices (again, using JSON through a converter).

As of now, much of the program is hardcoded for RockÉTS's rocket communication. Developpement into a proper ultra-configurable JSON-reading application will probably begin after Spaceport America Cup 2018 (so July 2018).

Do you think this is a stupid idea? I'm very open about any suggestions or criticism.