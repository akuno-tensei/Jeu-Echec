/*
	Nom du fichier : FenetreJeu.cpp
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "FenetreJeu.h"

Vue::FenetreJeu::FenetreJeu(QWidget* parent) :
	QMainWindow(parent)
{
	Modele::Table* table = new Modele::Table();
	table_ = std::unique_ptr<Modele::Table>(table);

	Vue::Echiquier* echiquier = new Vue::Echiquier(this);
	echiquier_ = std::unique_ptr<Vue::Echiquier>(echiquier);

	container_ = new QWidget();
	layoutPrincipal_ = new QVBoxLayout(container_);

	barreMenu_ = new QHBoxLayout();

	labelTour_ = new QLabel("Tour : Blancs");
	labelTour_->setStyleSheet("font-weight: bold; font-size: 16px;");

	boutonRecommencer_ = new QPushButton("Recommencer la partie");
	boutonChangerMode_ = new QPushButton("Changer de mode");

	barreMenu_->addWidget(labelTour_);
	barreMenu_->addStretch(); // Pousse les boutons vers la droite
	barreMenu_->addWidget(boutonRecommencer_);
	barreMenu_->addWidget(boutonChangerMode_);

	// Ajout de la barre et de l'échiquier au layout principal
	layoutPrincipal_->addLayout(barreMenu_);
	layoutPrincipal_->addWidget(echiquier_.get(), 0, Qt::AlignCenter);

	setCentralWidget(container_);

	Controleur* controleur = new Controleur(table, echiquier, this);
	controleur_ = std::unique_ptr<Controleur>(controleur);

	choixDePartie();

	connect(boutonRecommencer_, &QPushButton::clicked, controleur_.get(), &Controleur::rechargerPartie);

	connect(boutonChangerMode_, &QPushButton::clicked, this, &Vue::FenetreJeu::choixDePartie);

	connect(controleur_.get(), &Controleur::changementTour, this, &Vue::FenetreJeu::mettreAJourLabelTour);

	connect(controleur_.get(), &Controleur::promotion, this, &Vue::FenetreJeu::promotion);

	connect(echiquier_.get(), &Vue::Echiquier::caseCliquee, controleur_.get(), &Controleur::traiterClic);

	connect(controleur_.get(), &Controleur::partieTerminee, this, &Vue::FenetreJeu::choixDePartie);
}

void Vue::FenetreJeu::choixDePartie() {
	DialogueNouvellePartie diag(this);

	if (diag.exec() == QDialog::Accepted) {
		QString type = diag.obtenirTypePartie();

		controleur_->demarrerPartie(type);
	}
}

void Vue::FenetreJeu::promotion(const QPoint& position) {
	DialoguePromotion diag(this);

	if (diag.exec() == QDialog::Accepted) {
		QString promotion = diag.obtenirPromotion();

		table_->promouvoir(position, promotion);
	}

	echiquier_->rafraichir(table_.get());

	Modele::Couleur couleur = table_->obtenirPiece(position)->obtenirCouleur();

	if (couleur == Modele::Couleur::BLANC) {
		emit controleur_->changementTour("Tour : Noirs");
	}
	else {
		emit controleur_->changementTour("Tour : Blancs");
	}
}

Vue::FenetreJeu::~FenetreJeu() {
	delete container_;
}