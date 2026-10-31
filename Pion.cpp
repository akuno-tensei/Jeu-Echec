/*
	Nom du fichier : Pion.cpp
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Pion.h"

Modele::Pion::Pion(Couleur couleur, QPoint position) :
	Piece(couleur, position),
	posInitiale_(position)
{}

const char* Modele::Pion::obtenirCheminImage() const {
	if (obtenirCouleur() == Couleur::BLANC)
		return "images/pionBlanc.png";

	return "images/pionNoir.png";
}

std::vector<QPoint> Modele::Pion::mouvementsPossibles() const {
	std::vector<QPoint> deplacements;
	QPoint direction = (obtenirCouleur() == Couleur::BLANC) ? QPoint(0, 1) : QPoint(0, -1);

	if (obtenirPosition() == posInitiale_) {
		deplacements.push_back(obtenirPosition() + direction);
		deplacements.push_back(obtenirPosition() + direction + QPoint(-1, 0));
		deplacements.push_back(obtenirPosition() + direction + QPoint(1, 0));
		deplacements.push_back(obtenirPosition() + direction * 2);
	}
	else {
		deplacements.push_back(obtenirPosition() + direction);
		deplacements.push_back(obtenirPosition() + direction + QPoint(-1, 0));
		deplacements.push_back(obtenirPosition() + direction + QPoint(1, 0));
	}

	return deplacements;
}