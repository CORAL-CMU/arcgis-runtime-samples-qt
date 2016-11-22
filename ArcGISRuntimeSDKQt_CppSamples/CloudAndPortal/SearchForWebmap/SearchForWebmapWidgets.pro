#-------------------------------------------------
# Copyright 2015 Esri.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------

mac {
    cache()
}

#-------------------------------------------------------------------------------

CONFIG += c++11 arcgis_runtime_qml_cpp100_0_0

QT += opengl widgets positioning sensors

qtHaveModule(webengine) {
  QT += webengine
  DEFINES += QT_WEBVIEW_WEBENGINE_BACKEND
}

TEMPLATE = app
TARGET = SearchForWebmapWidgets

#-------------------------------------------------------------------------------

HEADERS +=  SearchForWebmapController.h \
            SearchForWebmapWidget.h \

SOURCES +=  mainWidgets.cpp \
            SearchForWebmapController.cpp \
            SearchForWebmapWidget.cpp \

RESOURCES += SearchForWebmapWidgets.qrc

#-------------------------------------------------------------------------------

win32 {
    LIBS += Ole32.lib
}

macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
}

FORMS += \
    SearchForWebmapWidget.ui
