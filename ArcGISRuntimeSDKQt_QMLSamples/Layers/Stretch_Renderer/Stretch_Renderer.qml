// [WriteFile Name=Stretch_Renderer, Category=Layers]
// [Legal]
// Copyright 2016 Esri.

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// [Legal]

import QtQuick 2.6
import QtQuick.Controls 1.4
import Esri.ArcGISRuntime 100.0
import Esri.ArcGISExtras 1.1

Rectangle {
    id: rootRectangle
    clip: true

    width: 800
    height: 600

    property real scaleFactor: System.displayScaleFactor
    property url dataPath: System.userHomePath + "/ArcGIS/Runtime/UnitTests/raster"

    MapView {
        id: mapView
        anchors.fill: parent

        Map {
            Basemap {
                RasterLayer {
                    id: rasterLayer

                    Raster {
                        path: dataPath + "/formats/SRTM/SRTMCalifornia.tif"
                    }
                }
            }
        }
    }

    StretchRenderer {
        id: stretchRendererDemLight

        PercentClipStretchParameters {
            min: 2
            max: 2
        }

        colorRamp: ColorRampDemLight {
        }
    }

    StretchRenderer {
        id: stretchRendererDemScreen

        PercentClipStretchParameters {
            min: 2
            max: 2
        }

        colorRamp: ColorRampDemScreen {
        }
    }

    StretchRenderer {
        id: stretchRendererElevation

        PercentClipStretchParameters {
            min: 2
            max: 2
        }

        colorRamp: ColorRampElevation {
        }
    }

    Column {
        anchors {
            left: parent.left
            top: parent.top
            margins: 10 * scaleFactor
        }
        spacing: 10

        Button {
            text: "ColorRamp DEM Light"
            width: 200 * scaleFactor
            onClicked: rasterLayer.renderer = stretchRendererDemLight
        }

        Button {
            text: "ColorRamp DEM Screen"
            width: 200 * scaleFactor
            onClicked: rasterLayer.renderer = stretchRendererDemScreen
        }

        Button {
            text: "ColorRamp Elevation"
            width: 200 * scaleFactor
            onClicked: rasterLayer.renderer = stretchRendererElevation
        }
    }

    // Neatline rectangle
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border {
            width: 0.5 * scaleFactor
            color: "black"
        }
    }
}
