/*
	Nom du fichier : FenetreJeu.h
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#include "Table.h"
#include "Echiquier.h"
#include "Controleur.h"
#include "DialogueNouvellePartie.h"
#include "DialoguePromotion.h"
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QMainWindow>
#include <QMessageBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma pop()

namespace Vue {

	class FenetreJeu : public QMainWindow {
		Q_OBJECT

	public:
		FenetreJeu(QWidget* parent = nullptr);
		~FenetreJeu();

		void mettreAJourLabelTour(QString texte) { labelTour_->setText(texte); }

	public slots:
		void choixDePartie();
		void promotion(const QPoint& position);

	private:
		std::unique_ptr<Vue::Echiquier> echiquier_;
		std::unique_ptr<Modele::Table> table_;
		std::unique_ptr<Controleur> controleur_;
		QWidget* container_;
		QVBoxLayout* layoutPrincipal_;
		QHBoxLayout* barreMenu_;
		QLabel* labelTour_;
		QPushButton* boutonRecommencer_;
		QPushButton* boutonChangerMode_;
	};

}