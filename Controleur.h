/*
    Nom du fichier : Controleur.h
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#pragma warning(disable: 4828)
#pragma warning(push, 0)
#include <QObject>
#include <QMessageBox>
#pragma warning(pop)
#include "Table.h"
#include "Echiquier.h"
#include "Piece.h"

enum class ModePartie { CLASSIQUE, FIN_1, FIN_2, FIN_3 };

class Controleur : public QObject {
    Q_OBJECT

    public:
        Controleur(Modele::Table* table, Vue::Echiquier* echiquier, QObject* parent = nullptr);
        void demarrerPartie(QString& type);
		void terminerPartie(Modele::Couleur perdant);

    signals:
	    void partieTerminee(Modele::Couleur perdant);
        void changementTour(const QString& texteTour);
        void promotion(const QPoint pos);

    public slots:
        void traiterClic(const QPoint& position);
        void rechargerPartie();

    private:
        Modele::Table* table_;
        Vue::Echiquier* echiquier_;
        Modele::Piece* pieceSelectionnee_ = nullptr;
        Modele::Couleur couleurTour_;
        ModePartie mode_;
};
