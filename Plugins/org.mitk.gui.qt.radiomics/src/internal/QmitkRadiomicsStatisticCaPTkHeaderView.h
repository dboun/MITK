/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#if !defined(QmitkRadiomicsStatisticCaPTkHeaderView_H__INCLUDED)
#define QmitkRadiomicsStatisticCaPTkHeaderView_H__INCLUDED

#include <org_mitk_gui_qt_radiomics_Export.h>
#include "ui_QmitkRadiomicsStatisticCaPTkHeaderViewControls.h"

#include <QWidget>
#include <QString>

#include <usAny.h>

class RADIOMICS_EXPORT QmitkRadiomicsStatisticCaPTkHeaderView : public QWidget
{
  Q_OBJECT

public:

  /*!
  \brief default constructor
  */
  explicit QmitkRadiomicsStatisticCaPTkHeaderView(QWidget *parent = nullptr);

  /*!
  \brief default destructor
  */
  virtual ~QmitkRadiomicsStatisticCaPTkHeaderView();

  QString GetMode();

  int GetLatticeWindow();
  int GetLatticeStep();

protected slots:

  void OnModeComboBoxCurrentTextChanged(const QString& text);
  void OnDefaultButtonClicked();

protected:
  void ResetLatticeParameters();

private:
  Ui::QmitkRadiomicsStatisticCaPTkHeaderViewControls *m_Controls;

};

#endif // !defined(QmitkRadiomicsStatisticCaPTkHeaderView_H__INCLUDED)


