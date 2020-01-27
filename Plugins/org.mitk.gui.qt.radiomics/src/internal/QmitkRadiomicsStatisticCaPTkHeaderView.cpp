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

    m_Controls->lineEdit_window->setValidator( new QDoubleValidator(0, 100000, 3, this) );
    m_Controls->lineEdit_step->setValidator( new QDoubleValidator(0, 100000, 3, this) );

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

int QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeRadius()
{
    return m_Controls->lineEdit_radius->text().toInt();
}

int QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeWindow()
{
    return m_Controls->lineEdit_window->text().toInt();
}

int QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeStep()
{
    return m_Controls->lineEdit_step->text().toInt();
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
    m_Controls->lineEdit_window->setText("6.3");
    m_Controls->lineEdit_step->setText("6.3");
}