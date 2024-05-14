#ifndef COMPTE_H
#define COMPTE_H

#include <string>


class Compte {
public:
    Compte(int numero);
    Compte(int numeroCompte, double solde, const std::string& type); 

    void Deposer(double montant);
    void Retirer(double montant); 
    
    void Afficher() const;



    int getNumeroCompte() const; // Add the accessor methods
    double getSolde() const;
    const std::string& getType() const; 


   void setNumeroCompte(int numeroCompte); // Add the mutator methods
   void setSolde(double solde);
   void setType(std::string type);

private:
    int numeroCompte;
    double solde;
    std::string type; 
};

#endif
