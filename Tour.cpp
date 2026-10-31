/*
    Nom du fichier : Tour.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Tour.h"

Modele::Tour::Tour(Couleur couleur, QPoint position) :
	Piece(couleur, position)
{}

const char* Modele::Tour::obtenirCheminImage() const {
    if (obtenirCouleur() == Couleur::BLANC)
        return "images/tourBlanche.png";

    return "images/tourNoire.png";
}

std::vector<QPoint> Modele::Tour::mouvementsPossibles() const {
    std::vector<QPoint> deplacements;

    for (int i = 0; i < 8; ++i) {
        if (i != obtenirPosition().x()) 
            deplacements.push_back(QPoint(i, obtenirPosition().y()));

        if (i != obtenirPosition().y()) 
            deplacements.push_back(QPoint(obtenirPosition().x(), i));
    }
    return deplacements;
}