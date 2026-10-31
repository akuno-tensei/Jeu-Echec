
/*
	Nom du fichier : DialogueNouvellePartie.h
	Crée le 27 mars 2026
	Modifié le 06 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

	Description : Définition de la classe DialogueNouvellePartie, 
					qui sera utilisée pour gérer les options de 
					nouvelle partie dans l'interface utilisateur. 
*/
#pragma once
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#pragma warning(pop)

namespace Vue {

	class DialogueNouvellePartie : public QDialog {
		public:
			DialogueNouvellePartie(QWidget* parent = nullptr);
			~DialogueNouvellePartie()  = default;

			QString obtenirTypePartie() const;

		private:
			QComboBox* choixPosition_;
	};

}