# QT5_Opencv4.4_MinGW[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)<br>
Build and test on MinGW64bit OpenCV4.4 w/ QT5 (Windows10)

There is a another repository where I put some strucutred 3D stuff there: https://github.com/jmysu/Stereo3D

Config OpenCV4.4 w/ following changes: <br>
<br>                            
| Option  | Modified OpenCV Variables |
| --- | --- |
| V   | WITH_QT _//With QT mouse UI_ |
| V   | WITH_OPENGL |
| V   | CMAKE_CXX_STANDARD_REQUIRED |
| Add | CMAKE_CXX_STANDARD 11 _//Fix undefined reference std:: issue_ |
| X   | OPENCV_ENABLE_ALLOCATOR_STATS _//Fix error:long_ |
| X   | ENABLE_PRECOMPILED_HEADERS  _//Fix math.h issue_ |
| Add | OPENCV_EXTRA_MODULES_PATH where_saved_path_of_opencv_contrib_modules | 
<br>
<br>
 
Rebuild OpenCV w/ Qt5.15.1-MinGW64bit... (remember to add openCV DLL path to system PATH)<br>

<br>

 __QT5 app for loading picture w/ OpenCV4...__ <br>
<img src="pic/OpenCV4TestPic.jpg" width=640 height=400/>
<br>

 __QT5 app for image editing w/ OpenCV4...__ <br>
(_from chap.02 in [Qt 5 and Open CV 4 Computer Vision Projects]_)<br>
<img src="pic/TheAwesomeChicken.jpg" width=480 height=300/>
<br>

 __QT5 app for adjusting depth map from stereo phtos w/ OpenCV4...__<br>
 (_from AbsurdePhoton_)<br>
<img src="pic/DisparityFilter.jpg" width=480 height=300/> <br>

<br>
<br>


## References
  - [OpenCV4.4](https://github.com/opencv) OpenCV Github repository w/ Opencv_contrib
  - [QT5.15](https://www.qt.io/download) _www.qt.io_ Where to download the QT5 framework
  - [Qt 5 and Open CV 4 Computer Vision Projects](https://www.youtube.com/playlist?list=PLeLcvrwLe187K3Ceoe3X3VMAa31591aO8) Watch YouTube clips online
  - [Disparity and depth maps with QT and OpenCV with support for classic image files and MPO stereo pairs](https://github.com/AbsurdePhoton/disparity-filtering-mpo) AbsurdePhoton: Depth map project on Github.

