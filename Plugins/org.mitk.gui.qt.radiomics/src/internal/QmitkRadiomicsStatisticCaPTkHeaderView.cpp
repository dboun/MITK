#include "QmitkRadiomicsStatisticCaPTkHeaderView.h"

#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>

QmitkRadiomicsStatisticCaPTkHeaderView::QmitkRadiomicsStatisticCaPTkHeaderView(
    QWidget* parent) : 
        QWidget(parent),
        m_Controls(new Ui::QmitkRadiomicsStatisticCaPTkHeaderViewControls)
{
    m_Controls->setupUi(this/*parent*/);
    
    m_Controls->comboBox_mode->addItems(QStringList() << "Normal" << "Lattice");

    m_Controls->lineEdit_radius->setValidator( new QDoubleValidator(0, 10000, 4, this) );
    m_Controls->lineEdit_step->setValidator( new QDoubleValidator(0, 10000, 4, this) );

    // this->ResetLatticeParameters();
    this->OnModeComboBoxCurrentTextChanged("Normal");

    connect(m_Controls->comboBox_mode, SIGNAL(currentTextChanged(const QString&)),
        this, SLOT(OnModeComboBoxCurrentTextChanged(const QString&))
    );

    connect(m_Controls->pushButton_default, SIGNAL(clicked()),
        this, SLOT(OnDefaultButtonClicked())
    );
}

QmitkRadiomicsStatisticCaPTkHeaderView::~QmitkRadiomicsStatisticCaPTkHeaderView()
{

}

QString QmitkRadiomicsStatisticCaPTkHeaderView::GetMode()
{
    return m_Controls->comboBox_mode->currentText();
}

float QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeRadius()
{
    return m_Controls->lineEdit_radius->text().toFloat();
}

float QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeStep()
{
    return m_Controls->lineEdit_step->text().toFloat();
}

void QmitkRadiomicsStatisticCaPTkHeaderView::OnModeComboBoxCurrentTextChanged(
    const QString& text)
{
    if (text == "Normal")
    {
        m_Controls->widget_latticeparamscontainer->setVisible(false);
    }
    else if (text == "Lattice")
    {
        m_Controls->widget_latticeparamscontainer->setVisible(true);
    }
}

void QmitkRadiomicsStatisticCaPTkHeaderView::OnDefaultButtonClicked()
{
    this->ResetLatticeParameters();
}

void QmitkRadiomicsStatisticCaPTkHeaderView::ResetLatticeParameters()
{
    m_Controls->lineEdit_radius->setText("2.0");
    m_Controls->lineEdit_step->setText("6.0");
}