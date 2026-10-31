/*
    Nom du fichier : Echiquier.h
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#include "Table.h"
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#pragma warning(pop)

namespace Vue {

    class Echiquier : public QGraphicsView {
        Q_OBJECT

        public:
            Echiquier(QWidget* parent = nullptr);
            void rafraichir(Modele::Table* table);
		    void miseEvidence(Modele::Table* table, Modele::Piece* piece);

        signals:
            void caseCliquee(const QPoint& position);

        protected:
            void mousePressEvent(QMouseEvent* event) override;

        private:
            QGraphicsScene* scene_;
    };

}