#-------------------------------------------------
#
# Pattern Paint
# http://blinkinlabs.com/patternpaint
#
# Copyright 2013, 2014, 2015, 2016, 2017 Blinkinlabs, LLC
#
#-------------------------------------------------

QT += widgets gui core

TARGET = PatternPaint
TEMPLATE = app

include(../libusb.pri)
include(../libblinky.pri)


# TODO: Push this entirely into libblinky, and don't refer
# serial directly in the GUI
QT += serialport


#Target version and application information
#VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}
include(../gitversion.pri)


DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"
DEFINES += APPLICATION_NAME=\\\"$${TARGET}\\\"
DEFINES += ORGANIZATION_NAME=\\\"Blinkinlabs\\\"
DEFINES += ORGANIZATION_DOMAIN=\\\"blinkinlabs.com\\\"

mac {
    QMAKE_TARGET_BUNDLE_PREFIX = com.blinkinlabs
}

# Disable updater checks when debugging, since the test app isn't signed and will fail anyway.
CONFIG(debug, debug|release) {
    message("Debug build, disabling app update checks")
    DEFINES += DISABLE_UPDATE_CHECKS
}

RESOURCES += \
    images.qrc \
    examples.qrc \
    translations.qrc

include(gui/gui.pri)
include(instruments/instruments.pri)
include(updater/updater.pri)


macx {
    # OS X: Specify icon resource to use
    ICON = images/patternpaint.icns

    # OS X: Specify our developer information using a custom plist
    QMAKE_INFO_PLIST = Info.plist
}

win32 {
    # Windows: Specify the icon to use
    RC_ICONS += images/patternpaint.ico
}
