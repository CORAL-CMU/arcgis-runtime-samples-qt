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

#ifndef COLORMAP_RENDERER_H
#define COLORMAP_RENDERER_H

namespace Esri
{
  namespace ArcGISRuntime
  {
    class MapQuickView;
    class RasterLayer;
  }
}

#include <QQuickItem>

class Colormap_Renderer : public QQuickItem
{
  Q_OBJECT

public:
  Colormap_Renderer(QQuickItem* parent = nullptr);
  ~Colormap_Renderer();

  void componentComplete() Q_DECL_OVERRIDE;

  Q_INVOKABLE void createColorMapRenderer();

private:
  Esri::ArcGISRuntime::MapQuickView* m_mapView;
  Esri::ArcGISRuntime::RasterLayer* m_rasterLayer;
  QString m_dataPath;
};

#endif // COLORMAP_RENDERER_H
