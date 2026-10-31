/*
    Nom du fichier : Roi.h
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/
 
#pragma once
#include "Piece.h"
#include "TropDeRois.h"


namespace Modele {

	class Roi : public Piece {
		public:
			Roi(Couleur couleur, QPoint position);
			~Roi();

			TypePiece obtenirType() const override { return TypePiece::ROI; }
			const char* obtenirCheminImage() const override;
			std::vector<QPoint> mouvementsPossibles() const override;

		private:
			static int compteurNoir_;
			static int compteurBlanc_;
	};
	
}