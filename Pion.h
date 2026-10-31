/*
	Nom du fichier : Pion.h
	Cr�e le 27 mars 2026
	Modifi� le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

/*
	Le déplacement des pièces ne s'effectue pas, j'ai pas réussi à résoudre le problème, j'ai essayé plusieurs approches mais sans succès.
*/

#pragma once
#include "Piece.h"

namespace Modele {

	class Pion : public Piece {
		public:
			Pion(Couleur couleur, QPoint position);

			TypePiece obtenirType() const override { return TypePiece::PION; }
			const char* obtenirCheminImage() const override;
			std::vector<QPoint> mouvementsPossibles() const override;
			bool estPositionInitiale() const { return obtenirPosition() == posInitiale_; }

		private:
			QPoint posInitiale_;
	};

}