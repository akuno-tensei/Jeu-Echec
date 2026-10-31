/*
	Nom du fichier : Table.h
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once

#include "Cavalier.h"
#include "Fou.h"
#include "Tour.h"
#include "Pion.h"
#include "Reine.h"
#include "Roi.h"
#include "Piece.h"
#include "DeplacementTemporaire.h"
#include "DialoguePromotion.h"
#include <memory>
#include <functional>
#include <map>
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QObject>
#pragma warning(pop)

namespace Modele {

	class Table : public QObject {
		Q_OBJECT	

		public:
			Table();

			std::map<int, std::map<int, std::shared_ptr<Modele::Piece>>>& obtenirGrille() { return grille_; }

			void clear();

			void initialiserClassique();

			void initialiserRoiReineFou();

			void initialiserRoiReineCavalier();

			void initialiserRoiReineTour();

			void ajouterPiece(std::shared_ptr<Piece>&& piece);

			Modele::Piece* obtenirPiece(const QPoint& position) const;

			void deplacerPiece(Modele::Piece* piece, const QPoint& cible);

			bool validerDeplacement(Modele::Piece* piece, const QPoint& cible);

			bool estDansTable(const QPoint& position) const { return position.x() >= 0 && position.x() < NB_CASES && position.y() >= 0 && position.y() < NB_CASES; }

			Piece* obtenirRoi(const Couleur& couleur) const;

			bool peutSecuriserRoi(Piece* piece, const QPoint& cible);

			bool peutBouger(const Couleur& couleur);

			bool estAttaque(Piece* p) const;

			bool pionPromotion(Piece* p, QPoint pos) const;

			void promouvoir(const QPoint& pos, QString promotion);

			std::vector<QPoint> filtrerMouvementsRoi(Piece* roi);

			std::vector<QPoint> filtrerMouvementsPossibles(Piece* piece) const;

			std::vector<QPoint> filtrerMouvementsPossiblesPrises(Piece* piece) const;

		private:
			std::map<int, std::map<int, std::shared_ptr<Modele::Piece>>> grille_;
			const unsigned int NB_CASES = 8;
	};

}