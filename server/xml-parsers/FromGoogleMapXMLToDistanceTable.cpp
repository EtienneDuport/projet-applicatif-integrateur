#include <stdio.h>
#include <iostream>
#include "FromGoogleMapXMLToDistanceTable.h"

// Constructeur
FromGoogleMapXMLToDistanceTable::FromGoogleMapXMLToDistanceTable() : LwSaxParser() {
    state = UNKNOWN;
    adresseCourante = "";
   numeroLigne = -1;
   
}


FromGoogleMapXMLToDistanceTable::~FromGoogleMapXMLToDistanceTable() {
    
}


std::vector<std::string> FromGoogleMapXMLToDistanceTable::getAdresses() {
    /* Pour l'instant, on triche, on remplie arbitrairement les adresses.
     *  -> Evidemment, il faudra effacer cette partie du code pour ne renvoyer que le vecteur adresses
     *     rempli par les autres méthodes à la lecture du fichier de réponse de GoogleMapAPI !
     */
    adresses.push_back("60 Rue de la Chimie, 38400 Saint-Martin-d'Hères, France");
    adresses.push_back("46 Avenue Félix Viallet, 38031 Grenoble, France");
    adresses.push_back("Rond-Point de la Croix de Vie, 38700 La Tronche, France");
     
    return adresses;
}

std::vector< std::vector<int> > FromGoogleMapXMLToDistanceTable::getDistances() {
   /* Pour l'instant, on triche, on remplie arbitrairement les adresses.
    *  -> Evidemment, il faudra effacer cette partie du code pour ne renvoyer que la matrice des distances
    *     remplie par les autres méthodes à la lecture du fichier de réponse de GoogleMapAPI !
    */
    
    
    std::vector<int> ligne0;
    ligne0.push_back(0);
    ligne0.push_back(5757);
    ligne0.push_back(7473);
    distanceMatrix.push_back(ligne0);
    
    std::vector<int> ligne1;
    ligne1.push_back(5782);
    ligne1.push_back(0);
    ligne1.push_back(3069);
    distanceMatrix.push_back(ligne1);
    
    std::vector<int> ligne2;
    ligne2.push_back(6822);
    ligne2.push_back(3339);
    ligne2.push_back(0);
    distanceMatrix.push_back(ligne2);    
    

    return distanceMatrix;
    
}


