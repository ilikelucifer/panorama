cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(StiPano2cam_V2)
				  
find_package (Qt5 COMPONENTS Gui Widgets Network OpenGL Xml)

#find PCL
#find_package (PCL 1.8.0 REQUIRED)
#include_directories (${PCL_INCLUDE_DIRS})
#link_directories    (${PCL_LIBRARY_DIRS})
#add_definitions     (${PCL_DEFINITIONS})

# find openCV
find_package (OpenCV 2.4.9 REQUIRED)
include_directories (${OpenCV_INCLUDE_DIRS})
link_directories    (${OpenCV_LIB_DIR})

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set  (PROJECT_SOURCES	
	main.cpp
    mainwindow.cpp
	renderwindow.cpp
	algorithms.cpp
	glwidget.cpp
	imgGraphicsView.cpp
	upload.cpp
	myImageView.cpp
	myImageViewRect.cpp
	myGraphicsEllipseItem.cpp
	myGraphicsRectItem.cpp
	folderimgs.cpp
	stitchTest.cpp
	myStitcher.cpp
	stiProcess.cpp
	query.cpp
	) 

set  (PROJECT_HEADERS
	ui_mainwindow.h
	ui_renderwindow.h
	ui_upload.h
	ui_folderimgs.h
	ui_query.h
	renderwindow.h
	mainwindow.h
	algorithms.h
	glwidget.h
	imgGraphicsView.h
	upload.h
	myImageView.h
	myImageViewRect.h
	myGraphicsEllipseItem.h
	myGraphicsRectItem.h
	folderimgs.h
	stitchTest.h
	myStitcher.h
	stiProcess.h
	query.h
	)
	


ADD_EXECUTABLE  (${PROJECT_NAME} ${PROJECT_SOURCES}
                        ${PROJECT_HEADERS}
					    ${PROJECT_RESOURCES})

TARGET_LINK_LIBRARIES ( ${PROJECT_NAME}  ${OpenCV_LIBS} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::OpenGL Qt5::Xml)