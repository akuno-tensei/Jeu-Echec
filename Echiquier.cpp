/*
    Nom du fichier : Echiquier.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Echiquier.h"

const unsigned int OFFSET = 10;
const unsigned int NB_CASES = 8;

const unsigned int Z_ORDER_FOND = 0;
const unsigned int Z_ORDER_EVIDENCE = 1;
const unsigned int Z_ORDER_PIECE = 2;
const unsigned int LINE_WIDTH = 3;

constexpr int TAILLE_CASE = 75;

Vue::Echiquier::Echiquier(QWidget* parent) : QGraphicsView(parent) {
    scene_ = new QGraphicsScene(this);
    setScene(scene_);
    setFixedSize(TAILLE_CASE * NB_CASES + OFFSET, TAILLE_CASE * NB_CASES + OFFSET);
}

void Vue::Echiquier::mousePressEvent(QMouseEvent* event) {
    QPointF p = mapToScene(event->pos());
    emit caseCliquee(QPoint(p.x() / TAILLE_CASE, p.y() / TAILLE_CASE));
}

void Vue::Echiquier::miseEvidence(Modele::Table* table, Modele::Piece* piece) {
	rafraichir(table);

    if (!piece)
		return;

    QColor evidence("#57b9d1");
    QColor selection("#ffc107");
    QColor prise("#e57373");

    QPen ligneBlanche(Qt::white);
    ligneBlanche.setWidth(LINE_WIDTH);
    ligneBlanche.setJoinStyle(Qt::MiterJoin); // pour des coins de cases uniformes

	auto* r = scene_->addRect(piece->obtenirPosition().x() * TAILLE_CASE, piece->obtenirPosition().y() * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
	r->setBrush(selection);
    r->setPen(ligneBlanche);
	r->setZValue(Z_ORDER_EVIDENCE);

    if (piece->obtenirType() == Modele::TypePiece::ROI) {
        for (const QPoint& pos : table->filtrerMouvementsRoi(piece)) {
            if (!table->estDansTable(pos))
                continue;

            auto* r = scene_->addRect(pos.x() * TAILLE_CASE, pos.y() * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

            if (!table->obtenirPiece(pos)) {
                r->setBrush(evidence);
            }
            else {
                r->setBrush(prise);
            }

            r->setPen(ligneBlanche);
            r->setZValue(Z_ORDER_EVIDENCE);
		}
        return;
    }

    for (const QPoint& pos : table->filtrerMouvementsPossibles(piece)) {
        if (!table->estDansTable(pos))
            continue;

        auto* r = scene_->addRect(pos.x() * TAILLE_CASE, pos.y() * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

        if (!table->obtenirPiece(pos)) {
            r->setBrush(evidence);
        }
        else {
            r->setBrush(prise);
        }

        r->setPen(ligneBlanche);
        r->setZValue(Z_ORDER_EVIDENCE);
    }
}

void Vue::Echiquier::rafraichir(Modele::Table* table) {
    scene_->clear();

    QColor couleurClaire("#f3d5ab");
    QColor couleurFoncee("#c37b42");

    QPen ligneBlanche(Qt::white);
    ligneBlanche.setWidth(LINE_WIDTH);
    ligneBlanche.setJoinStyle(Qt::MiterJoin);

    for (int i = 0; i < NB_CASES; ++i) {
        for (int j = 0; j < NB_CASES; ++j) {
            auto* r = scene_->addRect(i * TAILLE_CASE, j * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);

            r->setBrush((i + j) % 2 == 0 ? couleurClaire : couleurFoncee);
            r->setPen(ligneBlanche);
            r->setZValue(Z_ORDER_FOND);

            Modele::Piece* p = table->obtenirPiece(QPoint(i, j));

            if (p) {
                auto pieceImg = QPixmap(p->obtenirCheminImage());

                auto* img = scene_->addPixmap(pieceImg.scaled(TAILLE_CASE, TAILLE_CASE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
                img->setPos(i * TAILLE_CASE, j * TAILLE_CASE);
                img->setZValue(Z_ORDER_PIECE);
            }
        }
    }
}