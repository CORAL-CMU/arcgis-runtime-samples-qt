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

#ifndef RASTER_FUNCTION_H
#define RASTER_FUNCTION_H

namespace Esri
{
  namespace ArcGISRuntime
  {
    class MapQuickView;
    class RasterFunction;
    class RasterLayer;
  }
}

#include <QQuickItem>

class Raster_Function : public QQuickItem
{
  Q_OBJECT

public:
  Raster_Function(QQuickItem* parent = nullptr);
  ~Raster_Function();

  void componentComplete() Q_DECL_OVERRIDE;

private:
  Esri::ArcGISRuntime::MapQuickView* m_mapView;
  QString m_dataPath;

private:
  Esri::ArcGISRuntime::RasterFunction* createRasterFunction();
  void addRasterToNewMap(Esri::ArcGISRuntime::RasterLayer* rasterLayer);
};

#endif // RASTER_FUNCTION_H
