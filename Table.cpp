/*
    Nom du fichier : Table.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#include "Table.h"

constexpr unsigned int TAILLE = 8;

Modele::Table::Table() { grille_.clear(); }

void Modele::Table::ajouterPiece(std::shared_ptr<Piece>&& piece) {
    QPoint pos = piece->obtenirPosition();
    grille_[pos.x()][pos.y()] = std::move(piece);
}

void Modele::Table::clear() {
    grille_.clear();
}

void Modele::Table::initialiserRoiReineCavalier() {
	ajouterPiece(std::make_shared<Modele::Roi>(Couleur::BLANC, QPoint(4, 7)));
    ajouterPiece(std::make_shared<Modele::Roi>(Couleur::NOIR, QPoint(4, 0)));
	ajouterPiece(std::make_shared<Modele::Reine>(Couleur::NOIR, QPoint(1, 0)));
    ajouterPiece(std::make_shared<Modele::Cavalier>(Couleur::NOIR, QPoint(5, 3)));
}

void Modele::Table::initialiserRoiReineFou() {
    ajouterPiece(std::make_shared<Modele::Roi>(Couleur::BLANC, QPoint(4, 7)));
    ajouterPiece(std::make_shared<Modele::Roi>(Couleur::NOIR, QPoint(4, 0)));
    ajouterPiece(std::make_shared<Modele::Reine>(Couleur::NOIR, QPoint(2, 0)));
    ajouterPiece(std::make_shared<Modele::Fou>(Couleur::NOIR, QPoint(5, 3)));
}

void Modele::Table::initialiserRoiReineTour() {
    ajouterPiece(std::make_shared<Modele::Roi>(Couleur::BLANC, QPoint(4, 7)));
    ajouterPiece(std::make_shared<Modele::Roi>(Couleur::NOIR, QPoint(4, 0)));
    ajouterPiece(std::make_shared<Modele::Reine>(Couleur::NOIR, QPoint(0, 0)));
    ajouterPiece(std::make_shared<Modele::Tour>(Couleur::NOIR, QPoint(7, 0)));
}

void Modele::Table::initialiserClassique() {

    // test d'erreur : trop de rois
    // grille_[4][4] = std::make_unique<Roi>(Modele::Couleur::BLANC, QPoint(4, 4));

    for (unsigned int i = 0; i < TAILLE; ++i) {
       if (i > 1 && i < 6)
           continue;

       Modele::Couleur couleur = (i <= 1) ? Modele::Couleur::BLANC : Modele::Couleur::NOIR;

       for (unsigned int j = 0; j < TAILLE; ++j) {
           QPoint position(j, i);

           if (i == 1 || i == 6) {
              ajouterPiece(std::make_shared<Modele::Pion>(couleur, position));
           }
           else {
               switch (j) {
                   case 0:
                   case 7:
                       ajouterPiece(std::make_shared<Modele::Tour>(couleur, position));
                       break;
                   case 1:
                   case 6:
                       ajouterPiece(std::make_shared<Modele::Cavalier>(couleur, position));
                       break;
                   case 2:
                   case 5:
                       ajouterPiece(std::make_shared<Modele::Fou>(couleur, position));
                       break;
                   case 3:
                       ajouterPiece(std::make_shared<Modele::Reine>(couleur, position));
                       break;
                   case 4:
                       ajouterPiece(std::make_shared<Modele::Roi>(couleur, position));
                       break;
               }
           }
       }
    }
}

Modele::Piece* Modele::Table::obtenirPiece(const QPoint& position) const {
    if (grille_.count(position.x()) && grille_.at(position.x()).count(position.y()))
        return grille_.at(position.x()).at(position.y()).get();
    return nullptr;
}

Modele::Piece* Modele::Table::obtenirRoi(const Couleur& couleur) const {
    for (const auto& col : grille_) {
        for (const auto& piece : col.second) {
            if (piece.second && piece.second->obtenirType() == Modele::TypePiece::ROI && piece.second->obtenirCouleur() == couleur)
                return piece.second.get();
        }
    }
}

bool Modele::Table::estAttaque(Piece* p) const {

    if (!p) return false;

    for (const auto& col : grille_) {
        for (const auto& piece : col.second) {

            if (piece.second && piece.second->obtenirCouleur() != p->obtenirCouleur()) {

                std::vector<QPoint> mouvements = filtrerMouvementsPossiblesPrises(piece.second.get());

                if (std::find(mouvements.begin(), mouvements.end(), p->obtenirPosition()) != mouvements.end()) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Modele::Table::peutSecuriserRoi(Piece* piece, const QPoint& cible) {

    if (!piece) return false;

    Modele::Couleur couleur = piece->obtenirCouleur();

    QPoint posOrigine = piece->obtenirPosition();

    DeplacementTemporaire simulation(*this, posOrigine, cible);

    Piece* monRoi = obtenirRoi(piece->obtenirCouleur());

    if (!estAttaque(monRoi)) {
        piece->changerPositionSecours(cible);
        return true;
    }
    return false;
}

bool Modele::Table::peutBouger(const Couleur& couleur) {
    Piece* roi = obtenirRoi(couleur);
    std::vector<QPoint> mouvements;

    if (!filtrerMouvementsRoi(roi).empty())
        return true;

    for (const auto& col : grille_) {
        for (const auto& piece : col.second) {
            if (piece.second && piece.second->obtenirCouleur() == couleur) {
                if (piece.second->obtenirType() == Modele::TypePiece::PION) {
                    mouvements = piece.second->mouvementsPossibles();
                }
                else {
                    mouvements = filtrerMouvementsPossibles(piece.second.get());
                }
                    
				for (const auto& pos : mouvements) {
                    if (validerDeplacement(piece.second.get(), pos) && peutSecuriserRoi(piece.second.get(), pos)) {
                        return true;
                    }
				}
            }
        }
	}

	return false;
}

std::vector<QPoint> Modele::Table::filtrerMouvementsRoi(Piece* roi) {
    std::vector<QPoint> mouvements = filtrerMouvementsPossibles(roi);
    QPoint posOrigine = roi->obtenirPosition();

    std::vector<QPoint> mouvementsFiltres;

    for (const QPoint& pos : mouvements) {

        {
            DeplacementTemporaire simulation(*this, posOrigine, pos);

            if (!estAttaque(roi)) {
                mouvementsFiltres.push_back(pos);
            }
        }
    }
    return mouvementsFiltres;
}

std::vector<QPoint> Modele::Table::filtrerMouvementsPossiblesPrises(Piece* piece) const {
    std::vector<QPoint> mouvements = piece->mouvementsPossibles();
    std::vector<QPoint> mouvementsFiltres;

    if (piece->obtenirType() == Modele::TypePiece::PION) {
        for (auto& pos : mouvements) {
            auto ciblePiece = obtenirPiece(pos);
            int dx = pos.x() - piece->obtenirPosition().x();

            if (dx != 0) {
                if (ciblePiece != nullptr && ciblePiece->obtenirCouleur() != piece->obtenirCouleur()) {
                    mouvementsFiltres.push_back(pos);
                }
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::CAVALIER) {
        for (auto& pos : mouvements) {
            auto ciblePiece = obtenirPiece(pos);
            if (ciblePiece == nullptr || ciblePiece->obtenirCouleur() != piece->obtenirCouleur()) {
                mouvementsFiltres.push_back(pos);
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::ROI) {
        for (auto& pos : mouvements) {
            auto ciblePiece = obtenirPiece(pos);
            
            mouvementsFiltres.push_back(pos);
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::TOUR) {
        QPoint depart = piece->obtenirPosition();

        std::vector<QPoint> directions = { QPoint(0, 1), QPoint(0, -1), QPoint(1, 0), QPoint(-1, 0) };

        for (const QPoint& dir : directions) {
            QPoint courant = depart + dir;

            while (estDansTable(courant)) {
                Modele::Piece* cible = obtenirPiece(courant);

                if (cible == nullptr) {
                    mouvementsFiltres.push_back(courant);
                }
                else {
                    mouvementsFiltres.push_back(courant);
                    break;
                }
                courant += dir;
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::FOU) {
        QPoint depart = piece->obtenirPosition();

        std::vector<QPoint> directions = { QPoint(1, 1), QPoint(1, -1), QPoint(-1, 1), QPoint(-1, -1) };

        for (const QPoint& dir : directions) {
            QPoint courant = depart + dir;

            while (estDansTable(courant)) {
                Modele::Piece* cible = obtenirPiece(courant);

                if (cible == nullptr) {
                    mouvementsFiltres.push_back(courant);
                }
                else {
                    mouvementsFiltres.push_back(courant);
                    break;
                }
                courant += dir;
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::REINE) {
        QPoint depart = piece->obtenirPosition();

        std::vector<QPoint> directions = { QPoint(0, 1), QPoint(0, -1), QPoint(1, 0), QPoint(-1, 0),
                                            QPoint(1, 1), QPoint(1, -1), QPoint(-1, 1), QPoint(-1, -1) };

        for (const QPoint& dir : directions) {
            QPoint courant = depart + dir;

            while (estDansTable(courant)) {
                Modele::Piece* cible = obtenirPiece(courant);

                if (cible == nullptr) {
                    mouvementsFiltres.push_back(courant);
                }
                else {
                    mouvementsFiltres.push_back(courant);
                    break;
                }
                courant += dir;
            }
        }
    }

    return mouvementsFiltres;
}

std::vector<QPoint> Modele::Table::filtrerMouvementsPossibles(Piece* piece) const {
    std::vector<QPoint> mouvements = piece->mouvementsPossibles();
    std::vector<QPoint> mouvementsFiltres;

    if (piece->obtenirPositionSecours() != QPoint(-1, -1)) {
        mouvementsFiltres.push_back(piece->obtenirPositionSecours());
        return mouvementsFiltres;
    }
    else if (piece->obtenirType() == Modele::TypePiece::PION) {
        bool toutDroit = true;

        for (const QPoint& pos : mouvements) {
			auto ciblePiece = obtenirPiece(pos);

            if (pos.x() == piece->obtenirPosition().x()) {
                if (ciblePiece == nullptr && toutDroit) {
                    mouvementsFiltres.push_back(pos);
				}
                else if (ciblePiece != nullptr) {
                    toutDroit = false;
                }
            }
            else {
                if (ciblePiece != nullptr && ciblePiece->obtenirCouleur() != piece->obtenirCouleur()) {
                    mouvementsFiltres.push_back(pos);
                }
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::CAVALIER) {
        for (auto& pos : mouvements) {
            auto ciblePiece = obtenirPiece(pos);
            if (ciblePiece == nullptr || ciblePiece->obtenirCouleur() != piece->obtenirCouleur()) {
                mouvementsFiltres.push_back(pos);
            }
		}
    }
    else if (piece->obtenirType() == Modele::TypePiece::ROI) {
        for (auto& pos : mouvements) {
            auto ciblePiece = obtenirPiece(pos);

            if (ciblePiece == nullptr || ciblePiece->obtenirCouleur() != piece->obtenirCouleur()) {
                    mouvementsFiltres.push_back(pos);
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::TOUR) {
        QPoint depart = piece->obtenirPosition();

        std::vector<QPoint> directions = { QPoint(0, 1), QPoint(0, -1), QPoint(1, 0), QPoint(-1, 0) };

        for (const QPoint& dir : directions) {
            QPoint courant = depart + dir;

            while (estDansTable(courant)) {
                Modele::Piece* cible = obtenirPiece(courant);

                if (cible == nullptr) {
                    mouvementsFiltres.push_back(courant);
                }
                else if (cible->obtenirCouleur() == piece->obtenirCouleur()) {
                    break;
                }
                else if (cible->obtenirCouleur() != piece->obtenirCouleur()) {
                    mouvementsFiltres.push_back(courant);
                    break;
                }
                courant += dir;
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::FOU) {
        QPoint depart = piece->obtenirPosition();

        std::vector<QPoint> directions = { QPoint(1, 1), QPoint(1, -1), QPoint(-1, 1), QPoint(-1, -1) };

        for (const QPoint& dir : directions) {
            QPoint courant = depart + dir;

            while (estDansTable(courant)) {
                Modele::Piece* cible = obtenirPiece(courant);

                if (cible == nullptr) {
                    mouvementsFiltres.push_back(courant);
                }
                else if (cible->obtenirCouleur() == piece->obtenirCouleur()) {
                    break;
                }
                else if (cible->obtenirCouleur() != piece->obtenirCouleur()) {
                    mouvementsFiltres.push_back(courant);
                    break;
                }
                courant += dir;
            }
        }
    }
    else if (piece->obtenirType() == Modele::TypePiece::REINE) {
        QPoint depart = piece->obtenirPosition();

        std::vector<QPoint> directions = { QPoint(0, 1), QPoint(0, -1), QPoint(1, 0), QPoint(-1, 0),
                                            QPoint(1, 1), QPoint(1, -1), QPoint(-1, 1), QPoint(-1, -1) };

        for (const QPoint& dir : directions) {
            QPoint courant = depart + dir;

            while (estDansTable(courant)) {
                Modele::Piece* cible = obtenirPiece(courant);

                if (cible == nullptr) {
                    mouvementsFiltres.push_back(courant);
                }
                else if (cible->obtenirCouleur() == piece->obtenirCouleur()) {
                    break;
                }
                else if (cible->obtenirCouleur() != piece->obtenirCouleur()) {
                    mouvementsFiltres.push_back(courant);
                    break;
                }
                courant += dir;
            }
        }
	}

    return mouvementsFiltres;
}

bool Modele::Table::pionPromotion(Piece* p, QPoint pos) const {
    if (p->obtenirType() != Modele::TypePiece::PION)
        return false;

    if (pos.y() == 0 || pos.y() == NB_CASES - 1)
        return true;

    return false;
}

void Modele::Table::promouvoir(const QPoint& pos, QString promotion) {
    Couleur couleur = obtenirPiece(pos)->obtenirCouleur();

    grille_[pos.x()][pos.y()] = nullptr;

    if (promotion == "Cavalier") {
        grille_[pos.x()][pos.y()] = std::make_shared<Modele::Cavalier>(couleur, pos);
    }
    else if (promotion == "Fou") {
        grille_[pos.x()][pos.y()] = std::make_shared<Modele::Fou>(couleur, pos);
    }
    else if (promotion == "Reine") {
        grille_[pos.x()][pos.y()] = std::make_shared<Modele::Reine>(couleur, pos);
    }
    else if (promotion == "Tour") {
        grille_[pos.x()][pos.y()] = std::make_shared<Modele::Tour>(couleur, pos);
    }
}

bool Modele::Table::validerDeplacement(Modele::Piece* p, const QPoint& cible) {

    if (!estDansTable(cible))
        return false;
    
    std::vector<QPoint> deplacements;

    if (p->obtenirType() == TypePiece::ROI) {
        deplacements = filtrerMouvementsRoi(p);
    }
    else {
        deplacements = filtrerMouvementsPossibles(p);
    }
    
    auto it = std::find(deplacements.begin(), deplacements.end(), cible);

    if (it == deplacements.end()) 
        return false;

    Modele::Piece* surCible = obtenirPiece(cible);
    if (surCible && (surCible->obtenirCouleur() == p->obtenirCouleur())) 
        return false;

    return true;
}

void Modele::Table::deplacerPiece(Modele::Piece* piece, const QPoint& cible) {
    if (!piece) return;

    QPoint reset = QPoint(-1, -1);

    piece->changerPositionSecours(reset);

    QPoint anciennePos = piece->obtenirPosition();

    std::shared_ptr<Modele::Piece> ptrPiece = grille_[anciennePos.x()][anciennePos.y()];

    piece->changerPosition(cible);

    grille_[cible.x()][cible.y()] = ptrPiece;

    grille_[anciennePos.x()][anciennePos.y()] = nullptr;
}