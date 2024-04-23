#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "compte.h"
#include "pret.h"
#include "banque.h"

class GestionnaireBanque; 

class Client {
public:
    Client(); 
    Client(const std::string& nom, const std::string& adresse); 
    Client(const std::string& nom, const std::string& adresse, int numeroCompte, double solde);
    Client(const std::string& nom, const std::string& adresse, GestionnaireBanque& gestionnaire); 
        ~Client();

        const std::string& getNom() const;
        const std::string& getAdresse() const;
        const std::vector<Compte>& getComptes() const;
        void setNom(const std::string& nom);
        void setAdresse(const std::string& adresse);

        int getNumeroCompte(const std::string& type) const;
        void ouvrirPret(double montant, double taux, int duree, const std::string &dateDebutStr, const std::string &dateRemboursementStr, const std::string &dateHeureStr, const std::shared_ptr<Compte> &compteAssociePtr);
        void supprimerClient(const std::string &nom, const std::string &adresse, std::vector<Client> &clients);
        bool numeroCompteExists(int numeroCompte) const;
        void OuvrirNouveauCompte(const std::string &type);
        bool FermerCompte(int numeroCompte); // Add close account method
        void AfficherComptes() const;
        void afficherSoldeCompte(int numeroCompte) const; // Add display accounts method
        void crediterCompte(int numeroCompte, double montant);
        void debiterCompte(int numeroCompte, double montant);
        void afficherPrets() const; // Add other loan-related methods as needed
        

    private:
        std::string nom;
        std::string adresse;
        std::vector<Compte> comptes;
        std::vector<Pret> prets;
        GestionnaireBanque &gestionnaireBanque;

};

#endif
