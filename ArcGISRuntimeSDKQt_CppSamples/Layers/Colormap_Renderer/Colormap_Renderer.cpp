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

#include "Colormap_Renderer.h"

#include "Map.h"
#include "MapQuickView.h"
#include "Raster.h"
#include "RasterLayer.h"
#include "Basemap.h"
#include "ColormapRenderer.h"

#include <QUrl>
#include <QQmlProperty>
#include <QFile>
#include <QByteArray>
#include <QList>
#include <QColor>

using namespace Esri::ArcGISRuntime;

Colormap_Renderer::Colormap_Renderer(QQuickItem* parent /* = nullptr */):
  QQuickItem(parent),
  m_mapView(nullptr),
  m_rasterLayer(nullptr)
{
}

Colormap_Renderer::~Colormap_Renderer()
{
}

void Colormap_Renderer::componentComplete()
{
  QQuickItem::componentComplete();

  // find QML MapView component
  m_mapView = findChild<MapQuickView*>("mapView");
  m_mapView->setWrapAroundMode(WrapAroundMode::Disabled);

  // Create the raster and raster layer
  m_dataPath = QUrl(QQmlProperty::read(this, "dataPath").toString()).toLocalFile();
  Raster* raster = new Raster(m_dataPath + "/renderer/colormap/nlcd_2011_landcover.tif", this);
  m_rasterLayer = new RasterLayer(raster, this);

  // Add the raster to the map
  Basemap* basemap = new Basemap(m_rasterLayer, this);
  Map* map = new Map(basemap, this);
  m_mapView->setMap(map);
}

void Colormap_Renderer::createColorMapRenderer()
{
  QFile colorFile(m_dataPath + "/renderer/colormap/nlcd_2011_landcover.clr");

  if (colorFile.exists())
  {
    if (colorFile.open(QIODevice::ReadOnly))
    {
      // Get the color list from a text file
      QList<QColor> colorList;
      while (!colorFile.atEnd())
      {
        QByteArray line = colorFile.readLine();
        QList<QByteArray> parts = line.split(' ');
        int r = parts.at(1).trimmed().toInt();
        int g = parts.at(2).trimmed().toInt();
        int b = parts.at(3).trimmed().toInt();
        QColor color(r, g, b);
        colorList.append(color);
      }

      // Create a colormap renderer
      ColormapRenderer* colormapRenderer = new ColormapRenderer(colorList, this);

      // apply the renderer to the raster layer
      if (m_rasterLayer)
        m_rasterLayer->setRenderer(colormapRenderer);
    }
  }
}
