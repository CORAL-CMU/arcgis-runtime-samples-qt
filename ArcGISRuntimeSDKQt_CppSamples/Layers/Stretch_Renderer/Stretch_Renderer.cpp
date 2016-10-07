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

#include "Stretch_Renderer.h"

#include "Map.h"
#include "MapQuickView.h"
#include "Raster.h"
#include "RasterLayer.h"
#include "Basemap.h"
#include "StretchRenderer.h"
#include "PercentClipStretchParameters.h"

#include <QUrl>
#include <QQmlProperty>

using namespace Esri::ArcGISRuntime;

Stretch_Renderer::Stretch_Renderer(QQuickItem* parent /* = nullptr */):
  QQuickItem(parent),
  m_mapView(nullptr)
{
}

Stretch_Renderer::~Stretch_Renderer()
{
}

void Stretch_Renderer::componentComplete()
{
  QQuickItem::componentComplete();

  // find QML MapView component
  m_mapView = findChild<MapQuickView*>("mapView");
  m_mapView->setWrapAroundMode(WrapAroundMode::Disabled);

  // Create the raster and raster layer
  m_dataPath = QUrl(QQmlProperty::read(this, "dataPath").toString()).toLocalFile();
  Raster* raster = new Raster(m_dataPath + "/formats/SRTM/SRTMCalifornia.tif", this);
  m_rasterLayer = new RasterLayer(raster, this);

  // Add the raster to the map
  Basemap* basemap = new Basemap(m_rasterLayer, this);
  Map* map = new Map(basemap, this);
  m_mapView->setMap(map);
}

void Stretch_Renderer::applyStretchRenderer(StretchColorRampType colorRampType)
{
  // set up parameters
  PercentClipStretchParameters stretchParams(2, 2);
  PresetColorRampType presetColorRampType;
  if (colorRampType == StretchColorRampType::DemLight)
    presetColorRampType = PresetColorRampType::DemLight;
  else if (colorRampType == StretchColorRampType::DemScreen)
    presetColorRampType = PresetColorRampType::DemScreen;
  else if (colorRampType == StretchColorRampType::Elevation)
    presetColorRampType = PresetColorRampType::Elevation;
  else
    presetColorRampType = PresetColorRampType::None;

  // create the stretch renderer
  StretchRenderer* stretchRenderer = new StretchRenderer(stretchParams, QList<double>(), true, presetColorRampType, this);

  // apply the renderer to the layer
  m_rasterLayer->setRenderer(stretchRenderer);
}
