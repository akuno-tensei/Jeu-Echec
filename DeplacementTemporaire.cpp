/*
    Nom du fichier : DeplacementTemporaire.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "DeplacementTemporaire.h"
#include "Table.h"
#include "Echiquier.h"

Modele::DeplacementTemporaire::DeplacementTemporaire(Table& table,  const QPoint& source, const QPoint& destination) : 
    table_(table),
    positionSource_(source),
    positionDestination_(destination)
{
    auto& grille = table_.obtenirGrille();

    pieceCourante_ = grille[positionSource_.x()][positionSource_.y()];
    pieceSauvegardee_ = grille[positionDestination_.x()][positionDestination_.y()];

    grille[positionDestination_.x()][positionDestination_.y()] = pieceCourante_;
    grille[positionSource_.x()][positionSource_.y()] = nullptr;
    pieceCourante_->changerPosition(positionDestination_);
}

Modele::DeplacementTemporaire::~DeplacementTemporaire()
{   
    auto& grille = table_.obtenirGrille();

    pieceCourante_->changerPosition(positionSource_);
    grille[positionSource_.x()][positionSource_.y()] = pieceCourante_;
    grille[positionDestination_.x()][positionDestination_.y()] = pieceSauvegardee_;
}