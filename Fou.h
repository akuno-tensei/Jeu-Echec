/*
	Nom du fichier : Fou.h
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#include "Piece.h"

namespace Modele {

	class Fou : public Piece {
	public:
		Fou(Couleur couleur, QPoint position);

		const char* obtenirCheminImage() const override;
		std::vector<QPoint> mouvementsPossibles() const override;
		TypePiece obtenirType() const override { return TypePiece::FOU; }

	private:
		/* Pas d'attributs privés */
	};

}