/*
    Nom du fichier : Reine.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Reine.h"

Modele::Reine::Reine(Couleur couleur, QPoint position) :
	Piece(couleur, position)
{}

const char* Modele::Reine::obtenirCheminImage() const {
    if (obtenirCouleur() == Couleur::BLANC)
        return "images/reineBlanche.png";

    return "images/reineNoire.png";
}

std::vector<QPoint> Modele::Reine::mouvementsPossibles() const {
	std::vector<QPoint> deplacements;

    for (int dx = -8; dx <= 8; ++dx) {
        for (int dy = -8; dy <= 8; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            if (dx == 0 || dy == 0 || std::abs(dx) == std::abs(dy)) {

                QPoint cible = obtenirPosition() + QPoint(dx, dy);

                if (cible.x() >= 0 && cible.x() <= 7 && cible.y() >= 0 && cible.y() <= 7) {
                    deplacements.push_back(cible);
                }
            }
        }
    }
    return deplacements;
}