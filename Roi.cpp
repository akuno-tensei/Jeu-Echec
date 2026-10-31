/*
    Nom du fichier : Roi.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/
 
#include "Roi.h"

int Modele::Roi::compteurNoir_ = 0;
int Modele::Roi::compteurBlanc_ = 0;   

Modele::Roi::Roi(Couleur couleur, QPoint position) :
    Piece(couleur, position)
{
    if (couleur == Couleur::BLANC) {
        compteurBlanc_++;
    }
    else {
        compteurNoir_++;
    }

    if (compteurBlanc_ > 1) {
        throw Modele::TropDeRois();
    }
    else if (compteurNoir_ > 1) {
        throw Modele::TropDeRois();
    }
}

Modele::Roi::~Roi() {
    if (obtenirCouleur() == Couleur::BLANC) {
        compteurBlanc_--;
    }
    else {
        compteurNoir_--;
    }
}

const char* Modele::Roi::obtenirCheminImage() const {
    if (obtenirCouleur() == Couleur::BLANC)
        return "images/roiBlanc.png";

    return "images/roiNoir.png";
}

std::vector<QPoint> Modele::Roi::mouvementsPossibles() const {
    std::vector<QPoint> deplacements;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;

            QPoint pos = obtenirPosition() + QPoint(dx, dy);

            if (pos.x() > 7 || pos.x() < 0 || pos.y() > 7 || pos.y() < 0)
                continue;

            deplacements.push_back(obtenirPosition() + QPoint(dx, dy));
        }
    }
    return deplacements;
}