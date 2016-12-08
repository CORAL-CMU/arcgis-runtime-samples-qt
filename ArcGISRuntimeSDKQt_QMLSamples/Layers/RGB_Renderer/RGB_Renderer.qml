// [WriteFile Name=RGB_Renderer, Category=Layers]
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
                        path: dataPath + "/renderer/rgb/po_311944_bgrn_0000001.tif"
                    }
                }
            }
        }
    }

    // create an rgb renderer
    RGBRenderer {
        id: rgbRenderer1
        bandIndexes: [2, 1, 0]
        pansharpenType: Enums.PansharpenTypeMean
        Raster {
            path: dataPath + "/renderer/rgb/po_311944_pan_0000001.tif"
        }
        weights: [0.1, 0.5, 0.4, 0.3]
    }

    // create a second rgb renderer
    RGBRenderer {
        id: rgbRenderer2
        bandIndexes: [1, 2, 0]
        pansharpenType: Enums.PansharpenTypeNone
    }

    Column {
        anchors {
            left: parent.left
            top: parent.top
            margins: 10 * scaleFactor
        }
        spacing: 10

        Button {
            text: "Apply renderer 1"
            width: 150 * scaleFactor
            onClicked: rasterLayer.renderer = rgbRenderer1
        }

        Button {
            text: "Apply renderer 2"
            width: 150 * scaleFactor
            onClicked: rasterLayer.renderer = rgbRenderer2
        }

        Button {
            text: "Remove renderer"
            width: 150 * scaleFactor
            onClicked: rasterLayer.renderer = null
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
