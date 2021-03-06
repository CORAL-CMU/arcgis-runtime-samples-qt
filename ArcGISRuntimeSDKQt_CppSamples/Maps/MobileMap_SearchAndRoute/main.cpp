// Copyright 2015 Esri.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <QGuiApplication>
#include <QQuickView>
#include <QCommandLineParser>
#include <QDir>
#include <QQmlEngine>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include "MapQuickView.h"

#include "MobileMap_SearchAndRoute.h"

using namespace Esri::ArcGISRuntime;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

#ifdef Q_OS_WIN
    // Force usage of OpenGL ES through ANGLE on Windows
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif

    // Register the map view for QML
    qmlRegisterType<MapQuickView>("Esri.Samples", 1, 0, "MapView");
    qmlRegisterType<MobileMap_SearchAndRoute>("Esri.Samples", 1, 0, "MobileMap_SearchAndRouteSample");
    qmlRegisterUncreatableType<CalloutData>("Esri.Samples", 1, 0, "CalloutData", "CalloutData is an uncreatable type");

    // Intialize application view
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    // Add the import Path
    view.engine()->addImportPath(QDir(QCoreApplication::applicationDirPath()).filePath("qml"));

    // Set the source
    view.setSource(QUrl("qrc:/Samples/Maps/MobileMap_SearchAndRoute/MobileMap_SearchAndRoute.qml"));

    view.show();

    return app.exec();
}
