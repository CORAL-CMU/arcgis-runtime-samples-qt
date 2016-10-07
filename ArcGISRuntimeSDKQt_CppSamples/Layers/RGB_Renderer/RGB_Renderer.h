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

#ifndef RGB_RENDERER_H
#define RGB_RENDERER_H

namespace Esri
  {
  namespace ArcGISRuntime
  {
    class RasterLayer;
    class MapQuickView;
    class RGBRenderer;
  }
}

#include <QQuickItem>

class RGB_Renderer : public QQuickItem
{
  Q_OBJECT

public:
  RGB_Renderer(QQuickItem* parent = nullptr);
  ~RGB_Renderer();

  void componentComplete() Q_DECL_OVERRIDE;

  Q_INVOKABLE void applyRgbRenderer1();
  Q_INVOKABLE void applyRgbRenderer2();
  Q_INVOKABLE void clearRgbRenderer();

private:
  Esri::ArcGISRuntime::MapQuickView* m_mapView;
  Esri::ArcGISRuntime::RasterLayer* m_rasterLayer;
  QString m_dataPath;
};

#endif // RGB_RENDERER_H
