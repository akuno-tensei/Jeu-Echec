/*
    Nom du fichier : Fou.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Fou.h"

Modele::Fou::Fou(Couleur couleur, QPoint position) :
	Piece(couleur, position)
{}

const char* Modele::Fou::obtenirCheminImage() const {
	if (obtenirCouleur() == Couleur::BLANC)
		return "images/fouBlanc.png";

	return "images/fouNoir.png";
}

std::vector<QPoint> Modele::Fou::mouvementsPossibles() const {
    std::vector<QPoint> deplacements;

    for (int dx = -8; dx <= 8; ++dx) {
        for (int dy = -8; dy <= 8; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            if (abs(dx) != abs(dy))
                continue;

            QPoint pos = obtenirPosition() + QPoint(dx, dy);

            if (pos.x() > 7 || pos.x() < 0 || pos.y() > 7 || pos.y() < 0)
                continue;

            deplacements.push_back(obtenirPosition() + QPoint(dx, dy));
        }
    }
    return deplacements;
}