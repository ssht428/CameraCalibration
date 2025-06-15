QT       += core gui widgets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    setting.cpp \
    thirdparty/libcbdetect/board_energy.cc \
    thirdparty/libcbdetect/boards_from_corners.cc \
    thirdparty/libcbdetect/create_correlation_patch.cc \
    thirdparty/libcbdetect/filter_board.cc \
    thirdparty/libcbdetect/filter_corners.cc \
    thirdparty/libcbdetect/find_corners.cc \
    thirdparty/libcbdetect/find_modes_meanshift.cc \
    thirdparty/libcbdetect/get_image_patch.cc \
    thirdparty/libcbdetect/get_init_location.cc \
    thirdparty/libcbdetect/grow_board.cc \
    thirdparty/libcbdetect/image_normalization_and_gradients.cc \
    thirdparty/libcbdetect/init_board.cc \
    thirdparty/libcbdetect/non_maximum_suppression.cc \
    thirdparty/libcbdetect/plot_boards.cc \
    thirdparty/libcbdetect/plot_corners.cc \
    thirdparty/libcbdetect/polynomial_fit.cc \
    thirdparty/libcbdetect/refine_corners.cc \
    thirdparty/libcbdetect/score_corners.cc \
    thirdparty/libcbdetect/weight_mask.cc \
    thirdparty/libDockingPanes/DockingPaneManager.cpp \
    thirdparty/libDockingPanes/DockingPaneBase.cpp \
    thirdparty/libDockingPanes/DockingPaneClient.cpp \
    thirdparty/libDockingPanes/DockingPaneContainer.cpp \
    thirdparty/libDockingPanes/DockingPaneSplitterContainer.cpp \
    thirdparty/libDockingPanes/DockAutoHideButton.cpp \
    thirdparty/libDockingPanes/DockingPaneTitleWidget.cpp \
    thirdparty/libDockingPanes/DockingToolButton.cpp \
    thirdparty/libDockingPanes/DockingFrameFrameSticker.cpp \
    thirdparty/libDockingPanes/DockingFrameStickers.cpp \
    thirdparty/libDockingPanes/DockingPaneTabbedContainer.cpp \
    thirdparty/libDockingPanes/DockingPaneTabWidget.cpp \
    thirdparty/libDockingPanes/DockingPaneFlyoutWidget.cpp \
    thirdparty/libDockingPanes/DockingTargetWidget.cpp \
    thirdparty/libDockingPanes/DockingPaneGlowWidget.cpp \
    thirdparty/libDockingPanes/DockingPaneGlow.cpp

HEADERS += \
    mainwindow.h \
    setting.h \
    thirdparty/libcbdetect/board_energy.h \
    thirdparty/libcbdetect/boards_from_corners.h \
    thirdparty/libcbdetect/config.h \
    thirdparty/libcbdetect/create_correlation_patch.h \
    thirdparty/libcbdetect/filter_board.h \
    thirdparty/libcbdetect/filter_corners.h \
    thirdparty/libcbdetect/find_corners.h \
    thirdparty/libcbdetect/find_modes_meanshift.h \
    thirdparty/libcbdetect/get_image_patch.h \
    thirdparty/libcbdetect/get_init_location.h \
    thirdparty/libcbdetect/grow_board.h \
    thirdparty/libcbdetect/image_normalization_and_gradients.h \
    thirdparty/libcbdetect/init_board.h \
    thirdparty/libcbdetect/non_maximum_suppression.h \
    thirdparty/libcbdetect/plot_boards.h \
    thirdparty/libcbdetect/plot_corners.h \
    thirdparty/libcbdetect/polynomial_fit.h \
    thirdparty/libcbdetect/refine_corners.h \
    thirdparty/libcbdetect/score_corners.h \
    thirdparty/libcbdetect/weight_mask.h \
    thirdparty/libDockingPanes/DockingPaneManager.h\
    thirdparty/libDockingPanes/DockingPanes_global.h \
    thirdparty/libDockingPanes/DockingPaneBase.h \
    thirdparty/libDockingPanes/DockingPaneClient.h \
    thirdparty/libDockingPanes/DockingPaneContainer.h \
    thirdparty/libDockingPanes/DockingPaneSplitterContainer.h \
    thirdparty/libDockingPanes/DockAutoHideButton.h \
    thirdparty/libDockingPanes/DockingPaneTitleWidget.h \
    thirdparty/libDockingPanes/DockingToolButton.h \
    thirdparty/libDockingPanes/DockingFrameFrameSticker.h \
    thirdparty/libDockingPanes/DockingFrameStickers.h \
    thirdparty/libDockingPanes/DockingPaneTabbedContainer.h \
    thirdparty/libDockingPanes/DockingPaneTabWidget.h \
    thirdparty/libDockingPanes/DockingPaneFlyoutWidget.h \
    thirdparty/libDockingPanes/DockingTargetWidget.h \
    thirdparty/libDockingPanes/DockingPaneGlowWidget.h \
    thirdparty/libDockingPanes/DockingPaneGlow.h

FORMS += \
    mainwindow.ui \
    setting.ui

win32:CONFIG(release, debug|release): LIBS += -LD:/Learn/OpenCV411/opencv/build/x64/vc16/lib/ -lopencv_world4110
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Learn/OpenCV411/opencv/build/x64/vc16/lib/ -lopencv_world4110d
else:unix: LIBS += -LD:/Learn/OpenCV411/opencv/build/x64/vc16/lib/ -lopencv_world4110

INCLUDEPATH += D:/Learn/OpenCV411/opencv/build/include
DEPENDPATH += D:/Learn/OpenCV411/opencv/build/include


INCLUDEPATH += thirdparty \
thirdparty/libcbdetect \
thirdparty/libDockingPanes

RESOURCES += \
    pic.qrc \
    thirdparty/libDockingPanes/resources/images.qrc \
    qstyle/dark/darkstyle.qrc \
    qstyle/light/lightstyle.qrc

RC_ICONS = CameraCalibration.ico  #need put ico under .pro folder

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

