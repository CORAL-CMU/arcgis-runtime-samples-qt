// [WriteFile Name=Colormap_Renderer, Category=Layers]
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
                        path: dataPath + "/renderer/colormap/nlcd_2011_landcover.tif"
                    }
                }
            }
        }
    }

    function createColorMapRenderer() {
        // read the color text file
        var fileContents = colorFile.readTextFile("nlcd_2011_landcover.clr");
        var lines = fileContents.split("\n");

        // create a color from rgb values, and add to array
        var colorArray = [];
        for (var i = 0; i < lines.length; i++) {
            var rgbValues = lines[i].split(" ");
            if (rgbValues[1] && rgbValues[2] && rgbValues[3]) {
                var r = rgbValues[1].trim() / 255;
                var g = rgbValues[2].trim() / 255;
                var b = rgbValues[3].trim() / 255;
                var color = Qt.rgba(r, g, b);
                colorArray.push(color);
            }
        }

        // create a colormap
        var colormap = ArcGISRuntimeEnvironment.createObject("Colormap", {colors: colorArray});

        // create colormap renderer
        var colormapRenderer = ArcGISRuntimeEnvironment.createObject("ColormapRenderer", {colormap: colormap});

        // apply the renderer to the raster layer
        rasterLayer.renderer = colormapRenderer;
    }

    FileFolder {
        id: colorFile
        path: System.resolvedPath(dataPath) + "/renderer/colormap"
    }

    Button {
        anchors {
            left: parent.left
            top: parent.top
            margins: 10 * scaleFactor
        }
        text: "Apply renderer"
        onClicked: createColorMapRenderer()
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
