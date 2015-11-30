#include "LwSaxParser.h"
#include <vector>
#include <string>

class FromGoogleMapXMLToDistanceTable : public LwSaxParser {
    
public:
    // Enumération des différents états possible du parseur
    enum PossibleStates {START, ORIGIN_ADDRESS, ROW, ELEMENT, DISTANCE, VALUE, UNKNOWN};
    
    /// Constructeur
    FromGoogleMapXMLToDistanceTable();
    
    /// Desctructeur
    ~FromGoogleMapXMLToDistanceTable();
    
    /// Liste des adresses
    std::vector< std::string > getAdresses();
    
    /**
     * Distance en mètres entre les adresses
     * Le vecteur général est un vecteur de ligne.
     * Sur chaque ligne numéro i, il y a la distance entre l'adresses numéro i 
     *  et chacune des adresses numéro j (à la colonne j).
     */
    std::vector< std::vector<int> > getDistances();
    
protected:
   /** 
    * Méthodes ré-implemntées (surchargées) de la classe SaxParser
    * @{
    */
    // A compléter en recompiant la signature des méthodes à redéfinir
    
   /**
    * @}
    */
  
        
        
    /// Attributs
    
   /// Etat courant
   int state;
   
   std::string adresseCourante;
   
   /// Vecteur des adresses à remplir
   std::vector<std::string>  adresses;
   
   /// Ligne courante lors du remplissage
   int numeroLigne;   
   std::vector<int> ligne;
   
    /// Matrice des distances à remplir
    std::vector< std::vector<int> > distanceMatrix;
    
};
