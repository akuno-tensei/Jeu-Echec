/*
	Nom du fichier : Cavalier.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Cavalier.h"

Modele::Cavalier::Cavalier(Couleur couleur, QPoint position) :
	Piece(couleur, position)
{}

const char* Modele::Cavalier::obtenirCheminImage() const {
    if (obtenirCouleur() == Couleur::BLANC)
        return "images/cavalierBlanc.png";

    return "images/cavalierNoir.png";
}

std::vector<QPoint> Modele::Cavalier::mouvementsPossibles() const {
    std::vector<QPoint> deplacements;
    std::vector<QPoint> sauts = {
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}
    };

    for (const auto& saut : sauts) {
        QPoint pos = obtenirPosition() + saut;

        if (pos.x() > 7 || pos.x() < 0 || pos.y() > 7 || pos.y() < 0)
            continue;

        deplacements.push_back(obtenirPosition() + saut);
    }
    return deplacements;
}