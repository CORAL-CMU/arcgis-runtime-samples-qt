// [WriteFile Name=RasterLayerMosaicDataset, Category=Layers]
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

#include "RasterLayerMosaicDataset.h"

#include "Map.h"
#include "MapQuickView.h"
#include "MosaicDatasetRaster.h"
#include "RasterLayer.h"
#include "Basemap.h"

#include <QQmlProperty>
#include <QUrl>

using namespace Esri::ArcGISRuntime;

RasterLayerMosaicDataset::RasterLayerMosaicDataset(QQuickItem* parent /* = nullptr */):
  QQuickItem(parent),
  m_map(nullptr),
  m_mapView(nullptr)
{
}

RasterLayerMosaicDataset::~RasterLayerMosaicDataset()
{
}

void RasterLayerMosaicDataset::componentComplete()
{
  QQuickItem::componentComplete();

  QString dataPath = QUrl(QQmlProperty::read(this, "dataPath").toString()).toLocalFile();

  m_mapView = findChild<MapQuickView*>("mapView");
  m_mapView->setWrapAroundMode(WrapAroundMode::Disabled);

  // Create a mosaic dataset raster from sqlite mosaic dataset, and a table name
  MosaicDatasetRaster* mosaicDataset = new MosaicDatasetRaster(dataPath + "/mosaic_dataset/CADRG/hawaii.sqlite", "hawaii_bilinear", this);

  // Create a raster layer from the mosaic dataset raster
  RasterLayer* rasterLayer = new RasterLayer(mosaicDataset, this);

  // Add the raster layer to the map
  Basemap* basemap = new Basemap(rasterLayer, this);
  Map* map = new Map(basemap, this);
  m_mapView->setMap(map);
}
