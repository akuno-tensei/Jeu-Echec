/*
	Nom du fichier : Reine.h
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#include "Piece.h"

namespace Modele {

	class Reine : public Piece {
		public:
			Reine(Couleur couleur, QPoint position);

			TypePiece obtenirType() const override { return TypePiece::REINE; }
			const char* obtenirCheminImage() const override;
			std::vector<QPoint> mouvementsPossibles() const override;

		private:
			/* Pas d'attributs privés */
	};

}