# ♟️ Jeu d'échecs

Jeu d'échecs à deux joueurs (local, sur le même ordinateur) développé en **C++ avec Qt 6**. Le projet propose une partie classique ainsi que trois scénarios de **fins de partie** pour s'entraîner à mater avec une pièce donnée.

## Fonctionnalités

- Échiquier graphique 8×8 avec les pièces affichées en images
- Sélection d'une pièce par clic, avec **mise en évidence** de la pièce choisie
- Validation des coups pour toutes les pièces (pion, tour, cavalier, fou, reine, roi)
- Gestion de l'**échec** : un joueur en échec ne peut jouer qu'un coup qui sauve son roi, et le roi ne peut pas se placer sur une case attaquée
- Détection de la **fin de partie** (aucun coup légal) avec message de fin et choix de rejouer ou de quitter
- **Promotion du pion** avec choix de la pièce (reine, tour, cavalier ou fou)
- Indicateur du tour en cours (« Tour : Blancs » / « Tour : Noirs »)
- Boutons **Recommencer la partie** et **Changer de mode**

## Modes de jeu

| Mode | Description |
|------|-------------|
| Classique | Position de départ standard |
| Fin de partie : Roi, Reine et Tour | Les Blancs n'ont que leur roi ; les Noirs ont roi, reine et tour |
| Fin de partie : Roi, Reine et Fou | Les Blancs n'ont que leur roi ; les Noirs ont roi, reine et fou |
| Fin de partie : Roi, Reine et Cavalier | Les Blancs n'ont que leur roi ; les Noirs ont roi, reine et cavalier |

Le mode se choisit au lancement, puis peut être changé à tout moment avec le bouton « Changer de mode ».

## Prérequis

- **Windows** avec **Visual Studio 2022** (toolset MSVC v143)
- **Qt 6.11.0** (kit `msvc2022_64`) avec les modules `core`, `gui` et `widgets`
- Extension **Qt Visual Studio Tools** installée dans Visual Studio
- Compilateur compatible C++17 ou plus récent

> Le fichier de projet référence l'installation Qt `6.11.0_msvc2022_64`. Si votre version ou votre nom d'installation diffère, ajustez-le dans *Extensions → Qt VS Tools → Qt Versions*, puis dans les propriétés du projet (*Qt Project Settings*).

## Installation et lancement

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/akuno-tensei/Jeu-Echec.git
   cd Jeu-Echec
   ```
2. Ouvrir `projetEchec.sln` dans Visual Studio 2022.
3. Vérifier que la version de Qt est bien configurée (voir ci-dessus).
4. Choisir la configuration **x64 / Debug** (ou Release), puis compiler et lancer (`F5`).

**Important :** les images des pièces sont chargées via un chemin relatif (`images/...`). Le programme doit donc être exécuté avec le dossier du projet comme répertoire de travail, ce qui est le cas par défaut depuis Visual Studio. Si vous lancez l'exécutable à la main, faites-le depuis la racine du projet.

## Comment jouer

1. Choisissez un mode de partie dans la fenêtre de démarrage, puis cliquez sur **Lancer**.
2. Les **Blancs** commencent. Cliquez sur une de vos pièces pour la sélectionner.
3. Cliquez sur la case de destination pour jouer le coup. Cliquer ailleurs annule la sélection.
4. Quand un pion atteint la dernière rangée, choisissez sa promotion dans la boîte de dialogue.
5. La partie se termine lorsqu'un joueur n'a plus aucun coup légal. Vous pouvez alors rejouer ou quitter.

## Architecture

Le projet suit une séparation **Modèle / Vue / Contrôleur** (les namespaces `Modele` et `Vue` reflètent cette organisation).

```
Jeu-Echec/
├── main.cpp                   Point d'entrée de l'application Qt
│
├── Modèle (namespace Modele)
│   ├── Piece.h/.cpp           Classe abstraite de base des pièces
│   ├── Pion, Tour, Cavalier,
│   │   Fou, Reine, Roi        Pièces concrètes (.h/.cpp)
│   ├── Table.h/.cpp           Grille, initialisation des modes, validation des coups, échec, promotion
│   ├── DeplacementTemporaire  Simulation RAII d'un coup, annulée automatiquement à la destruction
│   └── TropDeRois.h           Exception levée si on crée plus d'un roi par couleur
│
├── Vue (namespace Vue)
│   ├── FenetreJeu             Fenêtre principale (tour, boutons)
│   ├── Echiquier              QGraphicsView qui dessine l'échiquier et capte les clics
│   ├── DialogueNouvellePartie Choix du mode de jeu
│   └── DialoguePromotion      Choix de la pièce de promotion
│
├── Controleur.h/.cpp          Logique de partie : tours, sélection, fin de partie
├── images/                    Sprites des pièces (PNG)
└── bibliotheque_cours/        Bibliothèque fournie dans le cadre du cours
```

Quelques choix de conception :

- **Polymorphisme** : chaque pièce hérite de `Piece` et fournit ses mouvements théoriques via `mouvementsPossibles()`. `Table` filtre ensuite ces mouvements (obstacles, prises, échec).
- **Simulation de coups (RAII)** : `DeplacementTemporaire` joue un coup fictif sur la table puis le défait dans son destructeur, ce qui permet de tester si un coup laisse le roi en échec sans modifier la partie.
- **Signaux et slots Qt** : l'échiquier émet `caseCliquee`, que le contrôleur traite ; le contrôleur émet à son tour `changementTour`, `promotion` et `partieTerminee` pour mettre à jour la vue.

## Limitations connues

- Le **roque** et la prise **en passant** ne sont pas implémentés.
- Il n'y a pas de gestion des **parties nulles** (pat, répétition, règle des 50 coups, matériel insuffisant). Une position sans coup légal est annoncée comme un échec et mat.
- Pas d'historique des coups, d'annulation de coup ni d'horloge.
- Pas de mode contre l'ordinateur : deux joueurs humains uniquement.
- Le pion de l'extrême gauche est le seul à ne pas pouvoir avancer de 2 cases au début d'une partie...

## Pistes d'amélioration

- Ajouter le roque et la prise en passant
- Ajouter une IA simple pour jouer en solo

## Auteurs

- Paul Tankeu Pajouo
- Diego Alejandro Monsalve Rivas

## Crédits

- Images des pièces : [Wikimedia Commons – PNG chess pieces (Standard transparent)](https://commons.wikimedia.org/wiki/Category:PNG_chess_pieces/Standard_transparent)
- [cppitertools](https://github.com/ryanhaining/cppitertools) et Microsoft GSL, inclus via la bibliothèque du cours