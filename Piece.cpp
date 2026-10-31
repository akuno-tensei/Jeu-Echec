/*
	Nom du fichier : Piece.cpp
	Crée le 27 mars 2026
	Modifié le 6 mai 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Piece.h"

Modele::Piece::Piece(Couleur couleur, QPoint position) :
	couleur_(couleur),
	position_(position),
	positionSecours_(QPoint(-1, -1))
{}
