/*
    Nom du fichier : Piece.h
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QPoint>
#pragma warning(pop)
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace Modele {

    enum class Couleur { BLANC, NOIR };

	enum class TypePiece { PION, TOUR, CAVALIER, FOU, REINE, ROI };

    class Piece {
        public:

            virtual ~Piece() = default;

            Couleur obtenirCouleur() const { return couleur_; }
            QPoint obtenirPosition() const { return position_; }
            void changerPosition(const QPoint& position) { position_ = position; }
            const QPoint& obtenirPositionSecours() const { return positionSecours_; }
            void changerPositionSecours(const QPoint& pos) { positionSecours_ = pos; }

            virtual const char* obtenirCheminImage() const = 0;
            virtual std::vector<QPoint> mouvementsPossibles() const = 0;
			virtual TypePiece obtenirType() const = 0;
        
        protected:
            Piece(Couleur couleur, QPoint position);

        private:
            Couleur couleur_;
            QPoint position_;
            QPoint positionSecours_;
    };

}