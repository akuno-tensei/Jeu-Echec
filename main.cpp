/*
    Nom du fichier : main.cpp
    Crée le 27 mars 2026
    Modifié le 6 mai 2026
    Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/


#include <iostream>
#include <QApplication>
#include "FenetreJeu.h"
/*
#include "bibliotheque_cours/verification_allocation.hpp"
#include "bibliotheque_cours/bibliotheque_cours.hpp"
#include "bibliotheque_cours/debogage_memoire.hpp"
*/

int main(int argc, char* argv[]) {
    /*
#pragma region "Bibliothèque du cours"
    // Permet sous Windows les "ANSI escape code" pour changer de couleur
    // https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
    // les supportent normalement par défaut.
    bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

    int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.
*/
    QApplication app(argc, argv);

    Vue::FenetreJeu fenetre;
    fenetre.show();

    // delete fuite;

    return app.exec();
}

