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

#include "RGB_Renderer.h"

#include "Map.h"
#include "MapQuickView.h"
#include "Raster.h"
#include "RasterLayer.h"
#include "Basemap.h"
#include "RGBRenderer.h"

#include <QUrl>
#include <QQmlProperty>

using namespace Esri::ArcGISRuntime;

RGB_Renderer::RGB_Renderer(QQuickItem* parent /* = nullptr */):
  QQuickItem(parent),
  m_mapView(nullptr),
  m_rasterLayer(nullptr)
{
}

RGB_Renderer::~RGB_Renderer()
{
}

void RGB_Renderer::componentComplete()
{
  QQuickItem::componentComplete();

  // find QML MapView component
  m_mapView = findChild<MapQuickView*>("mapView");
  m_mapView->setWrapAroundMode(WrapAroundMode::Disabled);

  // Create the raster and raster layer
  m_dataPath = QUrl(QQmlProperty::read(this, "dataPath").toString()).toLocalFile();
  Raster* raster = new Raster(m_dataPath + "/renderer/rgb/po_311944_bgrn_0000001.tif", this);
  m_rasterLayer = new RasterLayer(raster, this);

  // Add the raster to the map
  Basemap* basemap = new Basemap(m_rasterLayer, this);
  Map* map = new Map(basemap, this);
  m_mapView->setMap(map);
}

void RGB_Renderer::applyRgbRenderer1()
{
  // create an rgb renderer
  QList<int> bandIndexes = QList<int>() << 2 << 1 << 0;
  Raster* panchromaticRaster = new Raster(m_dataPath + "/renderer/rgb/po_311944_pan_0000001.tif", this);
  QList<double> weights = QList<double>() << 0.1 << 0.5 << 0.4 << 0.3;
  RGBRenderer* rgbRenderer = new RGBRenderer(StretchParameters(), bandIndexes, PansharpenType::Mean, panchromaticRaster, weights, this);

  // apply  renderer to raster layer
  m_rasterLayer->setRenderer(rgbRenderer);
}

void RGB_Renderer::applyRgbRenderer2()
{
  // create an rgb renderer
  QList<int> bandIndexes = QList<int>() << 1 << 2 << 0;
  Raster* panchromaticRaster = nullptr;
  QList<double> weights = QList<double>();
  RGBRenderer* rgbRenderer = new RGBRenderer(StretchParameters(), bandIndexes, PansharpenType::None, panchromaticRaster, weights, this);

  // apply  renderer to raster layer
  m_rasterLayer->setRenderer(rgbRenderer);
}

void RGB_Renderer::clearRgbRenderer()
{
  m_rasterLayer->setRenderer(nullptr);
}
