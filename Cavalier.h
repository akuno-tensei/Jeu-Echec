/*
	Nom du fichier : Cavalier.h
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#include "Piece.h"

namespace Modele {

	class Cavalier : public Piece {
		public:
			Cavalier(Couleur couleur, QPoint position);

			TypePiece obtenirType() const override { return TypePiece::CAVALIER; }
			const char* obtenirCheminImage() const override;
			std::vector<QPoint> mouvementsPossibles() const override;

		private:
			/* Pas d'attributs privés */
	};

}
