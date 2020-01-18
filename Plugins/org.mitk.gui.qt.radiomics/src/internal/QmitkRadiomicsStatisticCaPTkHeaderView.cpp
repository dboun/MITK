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

    // Default values
    // TODO: Limit them
    // TODO: Make them accept only numbers
    this->ResetLatticeParameters();
    this->OnSelectModeComboBoxCurrentTextChanged("Normal");

    connect(m_Controls->comboBox_mode, SIGNAL(currentTextChanged(const QString&)),
        this, SLOT(OnModeComboBoxCurrentTextChanged(const QString&))
    );

    connect(m_Controls->pushButton_reset, SIGNAL(clicked()),
        this, SLOT(OnResetButtonClicked())
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

int QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeNeighborhood()
{
    return m_Controls->lineEdit_neighborhood->text().toInt();
}

int QmitkRadiomicsStatisticCaPTkHeaderView::GetLatticeType()
{
    return m_Controls->lineEdit_type->text().toInt();
}

void QmitkRadiomicsStatisticCaPTkHeaderView::OnSelectModeComboBoxCurrentTextChanged(
    const QString& text)
{
    if (text == "Normal")
    {
    //     m_Controls->label_radius->setVisible(false);
    //     m_Controls->lineEdit_radius->setVisible(false);
    //     m_Controls->label_neighborhood->setVisible(false);
    //     m_Controls->lineEdit_neighborhood->setVisible(false);
    //     m_Controls->label_type->setVisible(false);
    //     m_Controls->lineEdit_type->setVisible(false);
    //     m_Controls->pushButton_reset->setVisible(false);
    }
    else if (text == "Lattice")
    {
    //     m_Controls->label_radius->setVisible(true);
    //     m_Controls->lineEdit_radius->setVisible(true);
    //     m_Controls->label_neighborhood->setVisible(true);
    //     m_Controls->lineEdit_neighborhood->setVisible(true);
    //     m_Controls->label_type->setVisible(true);
    //     m_Controls->lineEdit_type->setVisible(true);
    //     m_Controls->pushButton_reset->setVisible(true);
    }
}

void QmitkRadiomicsStatisticCaPTkHeaderView::OnResetButtonPressed()
{
    this->ResetLatticeParameters();
}

void QmitkRadiomicsStatisticCaPTkHeaderView::ResetLatticeParameters()
{
    m_Controls->lineEdit_radius->setText("1");
    m_Controls->lineEdit_neighborhood->setText("27");
    m_Controls->lineEdit_type->setText("2");
}