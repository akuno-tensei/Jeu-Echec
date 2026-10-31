/*
	Nom du fichier : TropDeRois.h
	Crée le 27 mars 2026
	Modifié le 21 avril 2026
	Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
*/

#pragma once
#include <stdexcept>

namespace Modele {
	class TropDeRois : public std::runtime_error {
		public:
			TropDeRois() : std::runtime_error("Erreur : Impossible de creer plus de deux rois de meme couleur.") {}
	};
}
