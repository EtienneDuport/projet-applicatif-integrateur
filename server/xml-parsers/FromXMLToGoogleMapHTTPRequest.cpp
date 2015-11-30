#include <string.h>
#include <iostream>
#include <curl.h>

#include "Address.h"

#include "FromXMLToGoogleMapHTTPRequest.h"

// Constructeur
FromXMLToGoogleMapHTTPRequest::FromXMLToGoogleMapHTTPRequest() : LwSaxParser()
{
    // On initialise les attributs...
    isCabinet = false;
    nurseId = "";
    currentState = OTHER;
    addressList = "";
    request = "";
    currentAddress = NULL;
}

FromXMLToGoogleMapHTTPRequest::~FromXMLToGoogleMapHTTPRequest() {
    // On libère l'adresse courante
    if (currentAddress != NULL) {
        delete currentAddress;
    }    
}


char * FromXMLToGoogleMapHTTPRequest::getGoogleHttpRequest(char * dataBaseFileName, int nurseNumber) {
    char * result;
    // Convertir l'entier nurseNumber en std::string pour pouvoir le stocker dans l'attribut id
    // Possible en C -> lire l'API doc de la méthode itoa ou sprintf
    // Plus simple en C++ en utilisant la STL
    std::ostringstream nbStr;
    if (nurseNumber < 100) {
        nbStr << "0";
    }
    if (nurseNumber < 10) {
        nbStr << "0";
    }
    nbStr << nurseNumber;
    nurseId = nbStr.str();
    std::cout << "Nurse Id: " << nurseId.c_str() << std::endl;
    
    // Parser le docuemnt
    // Le parsing a pour but de compléter addressList, l'instruction suivante la met en forme...
    parseDocument(dataBaseFileName);
   
    
    // Une fois que l'on a terminé le parsing du document, on converti la liste d'adresse en requête Google
    // et on la stocke dans l'attribut request de type std::string (plus facile à manipuler que char *).
    request = "origins=" + std::string(curl_easy_escape(NULL,addressList.c_str(),0)) + "&destinations=" + std::string(curl_easy_escape(NULL,addressList.c_str(),0));
    
    // Convertir la requête au format std::string en char *
    //    result = request.c_str(); -> ne fonctionne pas car request.c_str() renvoie quelque chose de const
    result = new char[request.length() + 1];
    strcpy(result, request.c_str());
        
    // Renvoyer le résultat    
    return result;
    
}

/*
 * Méthode d'aide qui permet de trouver un attribut qui a un certain nom dans une liste d'attribut.
 * Cette méthode existe de base dans l'API Sax de Java, mais pas ici, c'est pourquoi elle est donnée.
 */
std::string FromXMLToGoogleMapHTTPRequest::findAttribute(const AttributeList& attributeList, std::string attributeName) {
    std::string resultat = "";
    xmlpp::SaxParser::AttributeList::const_iterator iter = attributeList.begin();
    while ((iter != attributeList.end()) && (iter->name != attributeName)) {
        iter++;
    }
    if (iter != attributeList.end()) {
        resultat = iter->value;
    }
    return resultat;
}

