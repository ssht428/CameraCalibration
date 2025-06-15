# CameraCalibration

[<img src="doc/img/build_passing.png" width="100" alt="Build Status">](https://github.com/ssht428/CameraCalibration)
[<img src="doc/img/docs-mkdocs-blue.png" width="100" alt="Documentation">](https://github.com/ssht428/CameraCalibration)
[<img src="doc/img/license-MIT-blue.png" width="100" alt="GitHub license">](https://github.com/ssht428/CameraCalibration)
--------------
- [Design goals](#design-goals)
- [Dependence](#dependence)
- [Build and Run](#Build and Run)
---------------
## Design goals
A simple program for camera calibration based on Qt+OpenCV4,UI like Matlab's calibrate toolbox. Downside is mine ui :
[<img src="doc/img/ui_main.png" width="600" alt="UI Main">]
Downside is Matlab Calibration Toolbox UI :
[<img src="doc/img/matlab_camera_calib.png" width="600" alt="UI Main">]

## Dependence
1. Qt 5.14
2. OpenCV4.11
3. libcbdetect(https://github.com/ftdlyc/libcbdetect.git)
4. libDockingPanes(https://github.com/KestrelRadarSensors/dockingpanes) or Qt-Advanced-Docking-System(https://github.com/mfreiholz/Qt-Advanced-Docking-System)
5. nlohmann/json(https://github.com/nlohmann/json)   or pugixml(https://github.com/zeux/pugixml)


## Build and Run
1. Use cmake : ....
2. Direct use Qt open "CameraCalibration.pro" and build .
3. 