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

#include "Blend_Renderer.h"

#include "Map.h"
#include "MapQuickView.h"
#include "BlendRenderer.h"
#include "Raster.h"
#include "RasterLayer.h"
#include "RasterFunction.h"
#include "Basemap.h"

#include <QQmlProperty>
#include <QUrl>

using namespace Esri::ArcGISRuntime;

Blend_Renderer::Blend_Renderer(QQuickItem* parent /* = nullptr */):
  QQuickItem(parent),
  m_mapView(nullptr),
  m_rasterLayer(nullptr)
{
}

Blend_Renderer::~Blend_Renderer()
{
}

void Blend_Renderer::componentComplete()
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
  m_rasterLayer = new RasterLayer(raster, this);

  // add raster layer to the map
  addRasterToNewMap();
}

RasterFunction* Blend_Renderer::createRasterFunction()
{
  // create a RasterFunction
  RasterFunction* rasterFunction = new RasterFunction(m_dataPath + "/json/color.json");

  // set the number of rasters required - 2 in this case
  Raster* rasterArg1 = new Raster(m_dataPath + "/renderer/imgn23w160_13.tif");
  Raster* rasterArg2 = new Raster(m_dataPath + "/renderer/imgn23w160_13.tif");

  if (rasterFunction)
  {
    rasterFunction->arguments()->setRaster("raster", rasterArg1);
    rasterFunction->arguments()->setRaster("raster", rasterArg2);
  }

  return rasterFunction;
}

void Blend_Renderer::addRasterToNewMap()
{
  Basemap* basemap = new Basemap(m_rasterLayer, this);
  Map* map = new Map(basemap, this);
  m_mapView->setMap(map);
}

void Blend_Renderer::applyBlendRenderer()
{
  // create parameters
  Raster* elevationSource = new Raster(m_dataPath + "/renderer/imgn23w160_13.tif", this);
  double altitude(45.0);
  double azimuth(315.0);
  double zFactor(0.000015);
  ColorRamp* colorRamp = ColorRamp::create(PresetColorRampType::DemScreen, 500);

  SlopeType slopeType = SlopeType::Scaled;
  int pixelFactor =  1;
  int pixelPower =  1;
  int outputBitDepth =  8;

  // create blend renderer
  BlendRenderer* blendRenderer = new BlendRenderer(elevationSource, QList<double>() << 15.0 << 15.0 << 15.0, QList<double>() << 250.0 << 250.0 << 250.0,QList<double>() ,QList<double>() ,
                                                   QList<double>(), QList<double>(), colorRamp, altitude, azimuth, zFactor, slopeType, pixelFactor,
                                                   pixelPower, outputBitDepth, this);

  // apply to layer
  m_rasterLayer->setRenderer(blendRenderer);
}
