# QT5_Opencv4.4_MinGW[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)<br>
Build and test on MinGW64bit OpenCV4.4 w/ QT5

Config OpenCV4.4 w/ following changes: <br>

v   WITH_QT                           //With QT mouse UI <br>
v   WITH_OPENGL <br>
v   CMAKE_CXX_STANDARD_REQUIRED  <br>
Add CMAKE_CXX_STANDARD 11             //Fix undefined reference std::__cxx11 issue <br>
<br>
x   OPENCV_ENABLE_ALLOCATOR_STATS     //Fix error:long <br>
x   ENABLE_PRECOMPILED_HEADERS        //Fix math.h issue <br>
<br>
 

Rebuild OpenCV w/ Qt5.15.1-MinGW64bit...<br>


<br>
<br>
QT5 test app for loading picture w/ OpenCV<br>
<img src="pic/OpenCV4TestPic.jpg" width=720/>
<br><br>

<br><br>


## References
  - [OpenCV4.4] (https://github.com/opencv)  OpenCV4.4 repository and Opencv_contrib
  - [QT5.15] (https://www.qt.io/download) 



