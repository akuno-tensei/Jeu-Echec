#include "DialoguePromotion.h"

const unsigned int MIN_WIDTH = 350;
const unsigned int MIN_HEIGHT = 200;

Vue::DialoguePromotion::DialoguePromotion(QWidget* parent) : 
	QDialog(parent)
{
	setWindowTitle("Choisir la promotion");
	setModal(true);

	auto* layout = new QVBoxLayout(this);
	choixPosition_ = new QComboBox(this);

	choixPosition_->addItem("Reine");
	choixPosition_->addItem("Tour");
	choixPosition_->addItem("Cavalier");
	choixPosition_->addItem("Fou");

	auto* boutonValider = new QPushButton("Promouvoir", this);
	connect(boutonValider, &QPushButton::clicked, this, &QDialog::accept);

	layout->addWidget(choixPosition_);
	layout->addWidget(boutonValider);

	this->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
	this->adjustSize();
}

QString Vue::DialoguePromotion::obtenirPromotion() const {
	return choixPosition_->currentText();
}