#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "compte.h"
#include "client.h"
#include "pret.h"
#include "banque.h"
#include "transaction.h"
class Client;
class Compte;
class Pret;
class GestionnaireBanque; // Forward declaration of the GestionnaireBanque class

class Menu {
public:
    Menu(GestionnaireBanque& banque); // Constructor with bank reference
int choixUtilisateur;
    void afficherMenuPrincipal(){
        std::cout << "Choisissez une option :" << std::endl
          << "1. Gestion des clients" << std::endl
          << "2. Gestion des comptes" << std::endl
          << "3. Gestion des prets" << std::endl
          << "4. Quitter" << std::endl;
          std::cout << "Votre choix : "; std::cin >> choixUtilisateur;
        if (choixUtilisateur == 4) {
            std::cout << "goodbye !" << std::endl;
            exit(0);
        } else {
            afficherMenuPrincipal();
        } 
        std::cout << std::endl;
    }
    void afficherMenuGestionClients(){
        std::cout << "Choisissez une option :" << std::endl
          << "1. Ajouter un nouveau client" << std::endl
          << "2. Modifier un client existant" << std::endl
          << "3. Supprimer un client" << std::endl
          << "4. Retourner au menu principal"<< std::endl;
          std::cout << "Votre choix : "; std::cin >> choixUtilisateur;
        switch (choixUtilisateur) {
            case 1:
                gererNouveauClient();
                break;
            case 2:
                gererClientExistant();
                break;
            case 3:

                break;
            case 4:
                afficherMenuPrincipal();
                break;
            default:
                std::cout << "Choix invalide." << std::endl;
                break;
        } 
        std::cout << std::endl;
    }
    void afficherMenuGestionComptes(){
        std::cout << "Choisissez une option :" << std::endl
          << "1. Afficher la liste des comptes" << std::endl
          << "2. Afficher les details d'un compte" << std::endl
          << "3. Ouvrir un nouveau compte" << std::endl
          << "4. Fermer un compte" << std::endl 
          << "6. Deposer de l'argent sur un compte" << std::endl
          << "7. Retirer de l'argent d'un compte" << std::endl
          << "8. Effectuer un virement" << std::endl 
          << "10. Afficher la liste des comptes d'un client" << std::endl
          << "9. Afficher la liste des prets d'un client" << std::endl
          << "5. Retourner au menu principal"<< std::endl;
          std::cout << "Votre choix : "; std::cin >> choixUtilisateur;
        if (choixUtilisateur == 10) {
            afficherMenuPrincipal();
        } else {
            afficherMenuGestionComptes();
        } 
        std::cout << std::endl;
    }
    void afficherMenuGestionPrets(){
        std::cout << "Choisissez une option :" << std::endl
          << "1. Afficher la liste des prets" << std::endl
          << "2. Afficher les details d'un pret" << std::endl
          << "3. Demander un nouveau pret" << std::endl 
          << "4. Rembourser un pret" << std::endl
          << "5. Retourner au menu principal"<< std::endl;
          std::cout << "Votre choix : "; std::cin >> choixUtilisateur;
        if (choixUtilisateur == 5) {
            afficherMenuPrincipal();
        } else {
            afficherMenuGestionClients();
        } 
        std::cout << std::endl;
    }

public:
    Menu(GestionnaireBanque& banque) : banque(banque) {} // Constructor with bank reference
    void afficherMenuPrincipal();
    void afficherMenuGestionClients();
    void afficherMenuGestionComptes();
    void afficherMenuGestionPrets();


private:
    GestionnaireBanque& banque; // Reference to the bank object

    void gererNouveauClient();
    void gererClientExistant();
    void afficherDetailsCompte(const Compte& compte);
    void gererDepot(Compte& compte);
    void gererRetrait(Compte& compte);
    void gererVirement(const GestionnaireBanque& banque);
    void afficherListePrets(const Client& client);
    void gererNouveauPret(Client& client);
    void afficherDetailsPret(const Pret& pret);
    void gererPaiementPret(Pret& pret);
};

#endif
