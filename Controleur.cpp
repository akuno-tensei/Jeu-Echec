/*
    Nom du fichier : Controleur.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Controleur.h"

Controleur::Controleur(Modele::Table* table,  Vue::Echiquier* echiquier, QObject* parent) :
    QObject(parent), 
    table_(table), 
    echiquier_(echiquier),
    couleurTour_(Modele::Couleur::BLANC),
    mode_(ModePartie::CLASSIQUE)
{}

void Controleur::traiterClic(const QPoint& position) {

    Modele::Couleur couleurAdversaire = Modele::Couleur::BLANC;

    Modele::Piece* roi = table_->obtenirRoi(couleurTour_);
    bool roiEnEchec = table_->estAttaque(roi);

    Modele::Piece* piece = table_->obtenirPiece(position);
    bool estPermisSelection = piece && piece->obtenirCouleur() == couleurTour_;

    if (pieceSelectionnee_ == nullptr) {
        if (estPermisSelection) {
            if (!roiEnEchec) {
                pieceSelectionnee_ = piece;

                couleurAdversaire = (pieceSelectionnee_->obtenirCouleur() == Modele::Couleur::BLANC) ? 
                                     Modele::Couleur::NOIR : Modele::Couleur::BLANC;
            }
            else if (piece->obtenirType() == Modele::TypePiece::ROI) {
                if (!table_->filtrerMouvementsRoi(piece).empty()) {
                    pieceSelectionnee_ = piece;
                    couleurAdversaire = (pieceSelectionnee_->obtenirCouleur() == Modele::Couleur::BLANC) ?
                        Modele::Couleur::NOIR : Modele::Couleur::BLANC;
                }
            }
            else {
                auto mouvements = table_->filtrerMouvementsPossibles(piece);
                
                for (const QPoint& pos : mouvements) {
                    if (table_->validerDeplacement(piece, pos) && table_->peutSecuriserRoi(piece, pos)) {
                        pieceSelectionnee_ = piece;
                        couleurAdversaire = (pieceSelectionnee_->obtenirCouleur() == Modele::Couleur::BLANC) ? 
                                             Modele::Couleur::NOIR : Modele::Couleur::BLANC;
                        break;
                    }
                }
            }
        }
    }
    else {
        
        if (table_->validerDeplacement(pieceSelectionnee_, position)) {
            table_->deplacerPiece(pieceSelectionnee_, position);

            if (table_->pionPromotion(pieceSelectionnee_, position)) {
                emit promotion(position);
            }
        
            echiquier_->rafraichir(table_);

            if (!table_->peutBouger(couleurAdversaire)) {
                terminerPartie(couleurAdversaire);
                return;
            }

            if (pieceSelectionnee_->obtenirCouleur() == Modele::Couleur::BLANC) {
                couleurTour_ = Modele::Couleur::NOIR;
                emit changementTour("Tour : Noirs");
            }
            else {
                couleurTour_ = Modele::Couleur::BLANC;
                emit changementTour("Tour : Blancs");
            }
        }
        pieceSelectionnee_ = nullptr;
    }

    if (!table_->peutBouger(couleurTour_)) {
        terminerPartie(couleurTour_);
        return;
    }

    echiquier_->miseEvidence(table_, pieceSelectionnee_);
}

void Controleur::rechargerPartie() {
    table_->clear();
    couleurTour_ = Modele::Couleur::BLANC;
    pieceSelectionnee_ = nullptr;

    try {
        switch (mode_) {
            case ModePartie::CLASSIQUE:
                table_->initialiserClassique();
                break;

            case ModePartie::FIN_1:
                table_->initialiserRoiReineTour();
                break;

            case ModePartie::FIN_2:
                table_->initialiserRoiReineCavalier();
                break;

            case ModePartie::FIN_3:
                table_->initialiserRoiReineFou();
                break;

            default:
                table_->initialiserClassique();
                break;
        }
        echiquier_->rafraichir(table_);
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors du démarrage de la partie : " << e.what() << std::endl;
    }
}

void Controleur::demarrerPartie(QString& type) {
	table_->clear();
    couleurTour_ = Modele::Couleur::BLANC;
    pieceSelectionnee_ = nullptr;

    try {
        if (type == "Classique") {
            mode_ = ModePartie::CLASSIQUE;

            table_->initialiserClassique();
            echiquier_->rafraichir(table_);
        }
        else if (type == "Fin de partie : Roi, Reine et Tour") {
            mode_ = ModePartie::FIN_1;

			table_->initialiserRoiReineTour();
            echiquier_->rafraichir(table_);
        }
		else if (type == "Fin de partie : Roi, Reine et Cavalier") {
            mode_ = ModePartie::FIN_2;

            table_->initialiserRoiReineCavalier();
			echiquier_->rafraichir(table_);
        }
        else if (type == "Fin de partie : Roi, Reine et Fou") {
            mode_ = ModePartie::FIN_3;

            table_->initialiserRoiReineFou();
            echiquier_->rafraichir(table_);
        }
        else {
            mode_ = ModePartie::CLASSIQUE;

            table_->initialiserClassique();
            echiquier_->rafraichir(table_);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors du démarrage de la partie : " << e.what() << std::endl;
    }
}

void Controleur::terminerPartie(Modele::Couleur perdant) {
    QString message = (perdant == Modele::Couleur::BLANC)
        ? "Echec et Mat ! Les Noirs gagnent."
        : "Echec et Mat ! Les Blancs gagnent.";

    QMessageBox msgBox;
    msgBox.setWindowTitle("Fin de partie");
    msgBox.setText(message);
    msgBox.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Retry);

    int ret = msgBox.exec();

    if (ret == QMessageBox::Retry) {
        emit partieTerminee(perdant);
    }
    else {
        qApp->quit();
    }
}
