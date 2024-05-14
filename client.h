#ifndef CLIENT_H
#define CLIENT_H

#include 

class Client {
private:
    int id;
    std::string nom;
    std::string adresse; 

public:
    // Constructor
    Client(int id, const std::string& nom, const std::string& adresse = "");

    // Getters
    int getId() const;
    std::string getNom() const;
    std::string getAdresse() const; 

    // Setters
    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse); 
};

#endif