// [WriteFile Name=Raster_Function, Category=Layers]
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

#include "Raster_Function.h"

#include "Map.h"
#include "MapQuickView.h"
#include "Raster.h"
#include "RasterFunction.h"
#include "RasterFunctionArguments.h"
#include "RasterLayer.h"
#include "Basemap.h"

#include <QQmlProperty>
#include <QUrl>

using namespace Esri::ArcGISRuntime;

Raster_Function::Raster_Function(QQuickItem* parent /* = nullptr */):
  QQuickItem(parent),
  m_mapView(nullptr)
{
}

Raster_Function::~Raster_Function()
{
}

void Raster_Function::componentComplete()
{
  QQuickItem::componentComplete();

  m_dataPath = QUrl(QQmlProperty::read(this, "dataPath").toString()).toLocalFile();

  // find QML MapView component
  m_mapView = findChild<MapQuickView*>("mapView");
  m_mapView->setWrapAroundMode(WrapAroundMode::Disabled); 

  // create raster function
  RasterFunction* rasterFunction = createRasterFunction();

  // create raster from raster function
  Raster* raster = new Raster(rasterFunction, this);

  // raster raster layer from raster
  RasterLayer* rasterLayer = new RasterLayer(raster, this);

  // add raster layer to the map
  addRasterToNewMap(rasterLayer);
}

RasterFunction* Raster_Function::createRasterFunction()
{
  // create a RasterFunction
  RasterFunction* rasterFunction = new RasterFunction(m_dataPath + "/json/color.json");

  // set the number of rasters required - 2 in this case
  Raster* rasterArg1 = new Raster(m_dataPath + "/function/dem/gebco_08.tif");
  Raster* rasterArg2 = new Raster(m_dataPath + "/function/dem/gebco_08.tif");
  rasterFunction->arguments()->setRaster("raster", rasterArg1);
  rasterFunction->arguments()->setRaster("raster", rasterArg2);

  return rasterFunction;
}

void Raster_Function::addRasterToNewMap(RasterLayer* rasterLayer)
{
  Basemap* basemap = new Basemap(rasterLayer, this);
  Map* map = new Map(basemap, this);
  m_mapView->setMap(map);
}
