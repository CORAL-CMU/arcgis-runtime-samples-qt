// [WriteFile Name=Blend_Renderer, Category=Layers]
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
    property RasterLayer rasterLayer: null

    MapView {
        id: mapView
        anchors.fill: parent
    }

    BlendRenderer {
        id: blendRenderer
        elevationRaster: Raster {
            path: dataPath + "/renderer/imgn23w160_13.tif"
        }
        colorRamp: ColorRampDemScreen{
            size: 500
        }
        outputMinValues: [15.0]
        outputMaxValues: [250.0]
        altitude: 45
        azimuth: 315
        zFactor: 0.000015
        slopeType: Enums.SlopeTypeScaled
        pixelSizeFactor: 1
        pixelSizePower: 1
        outputBitDepth: 8
    }

    Column {
        anchors {
            left: parent.left
            top: parent.top
            margins: 10 * scaleFactor
        }
        spacing: 10

        Button {
            text: "Apply Blend Renderer"
            width: 200 * scaleFactor
            onClicked: rasterLayer.renderer = blendRenderer
        }
    }

    Component.onCompleted: {
        // create raster function
        var rasterFunction = createRasterFunction();

        // create the resulting raster
        var raster = ArcGISRuntimeEnvironment.createObject("Raster", {rasterFunction: rasterFunction});

        // create raster layer from raster
        rasterLayer = ArcGISRuntimeEnvironment.createObject("RasterLayer", {raster: raster});

        // add raster to map
        addRasterToNewMap(rasterLayer);
    }

    function createRasterFunction() {
        var rasterFunction = ArcGISRuntimeEnvironment.createObject("RasterFunction", {path: dataPath + "/json/color.json"});

        // set raster function arguments
        var rasterArg1 = ArcGISRuntimeEnvironment.createObject("Raster", {path: dataPath + "/renderer/imgn23w160_13.tif"});
        var rasterArg2 = ArcGISRuntimeEnvironment.createObject("Raster", {path: dataPath + "/renderer/imgn23w160_13.tif"});
        if (rasterFunction) {
            rasterFunction.arguments.setRaster("raster", rasterArg1);
            rasterFunction.arguments.setRaster("raster", rasterArg2);
        }

        return rasterFunction;
    }

    function addRasterToNewMap(rasterLayer) {
        var newBasemap = ArcGISRuntimeEnvironment.createObject("Basemap");
        newBasemap.baseLayers.append(rasterLayer);
        var newMap = ArcGISRuntimeEnvironment.createObject("Map", {basemap: newBasemap});
        mapView.map = newMap;
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
