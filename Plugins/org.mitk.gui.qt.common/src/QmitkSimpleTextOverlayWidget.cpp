/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#include "QmitkSimpleTextOverlayWidget.h"

#include <berryWorkbenchPlugin.h>
#include <berryQtStyleManager.h>

#include "QTextDocument"
#include "QPainter"

QmitkSimpleTextOverlayWidget::QmitkSimpleTextOverlayWidget(QWidget* parent)
  : QmitkOverlayWidget(parent)
{
}

QmitkSimpleTextOverlayWidget::~QmitkSimpleTextOverlayWidget()
{
}

QString QmitkSimpleTextOverlayWidget::GetOverlayText() const
{
  return m_Text;
}

void QmitkSimpleTextOverlayWidget::SetOverlayText(const QString& text)
{
  m_Text = text;
  this->update();
}

void QmitkSimpleTextOverlayWidget::paintEvent(QPaintEvent* p)
{
  QmitkOverlayWidget::paintEvent(p);

  QString stylesheet;

  ctkPluginContext* context = berry::WorkbenchPlugin::GetDefault()->GetPluginContext();
  ctkServiceReference styleManagerRef = context->getServiceReference<berry::IQtStyleManager>();
  if (styleManagerRef)
  {
    auto styleManager = context->getService<berry::IQtStyleManager>(styleManagerRef);
    stylesheet = styleManager->GetStylesheet();
  }

  QPainter painter(this);
  QTextDocument td(this);
  td.setDefaultStyleSheet(stylesheet);

  auto widgetSize = this->size();
  td.setTextWidth(widgetSize.width()-20.);
  QPoint origin = QPoint(10, 5);

  td.setHtml(m_Text);

  auto textSize = td.size();

  origin.setX((widgetSize.width() - textSize.width()) / 2.);
  origin.setY((widgetSize.height() - textSize.height()) / 2.);

  painter.translate(origin);
  td.drawContents(&painter);
}
