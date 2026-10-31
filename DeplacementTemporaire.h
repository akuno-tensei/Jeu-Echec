/*
    Nom du fichier : DeplacementTemporaire.h
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#pragma warning(disable: 4828)
#include <memory>
#include <QPoint>
#include "Piece.h"

namespace Modele {
    class Table;
}

namespace Modele {

    class DeplacementTemporaire {
        public:
            DeplacementTemporaire(Table& table, const QPoint& source, const QPoint& destination);

            DeplacementTemporaire(const DeplacementTemporaire&) = delete;
            DeplacementTemporaire& operator=(const DeplacementTemporaire&) = delete;

            ~DeplacementTemporaire();

        private:
            Table& table_;
            std::shared_ptr<Piece> pieceCourante_;
		    std::shared_ptr<Piece> pieceSauvegardee_;
            QPoint positionSource_;
            QPoint positionDestination_;
    };

}