
/*
	Nom du fichier : DialogueNouvellePartie.cpp
	Crée le 27 mars 2026
	Modifié le 06 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

	Description : Implémentation de la classe DialogueNouvellePartie, 
					qui sera utilisée pour gérer les options de 
					nouvelle partie dans l'interface utilisateur. 
*/

#include "DialogueNouvellePartie.h"

const unsigned int MIN_WIDTH = 350;
const unsigned int MIN_HEIGHT = 200;


Vue::DialogueNouvellePartie::DialogueNouvellePartie(QWidget* parent) : 
	QDialog(parent)
{
	setWindowTitle("Demarrer une nouvelle partie");
	setModal(true);

	auto* layout = new QVBoxLayout(this);
	choixPosition_ = new QComboBox(this);

	choixPosition_->addItem("Classique");
	choixPosition_->addItem("Fin de partie : Roi, Reine et Tour");
	choixPosition_->addItem("Fin de partie : Roi, Reine et Fou");
	choixPosition_->addItem("Fin de partie : Roi, Reine et Cavalier");

	auto* boutonValider = new QPushButton("Lancer", this);
	connect(boutonValider, &QPushButton::clicked, this, &QDialog::accept);

	layout->addWidget(choixPosition_);
	layout->addWidget(boutonValider);

	this->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
	this->adjustSize();
}

QString Vue::DialogueNouvellePartie::obtenirTypePartie() const {
	return choixPosition_->currentText();
}
