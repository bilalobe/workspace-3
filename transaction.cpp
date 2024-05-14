#include "transaction.h"
#include "banque.h" // Include the banque.h header file
#include "compte.h"
#include "client.h"
#include "logutils.h"

#include <fstream>
#include <sstream>
#include <vector>


GestionnaireBanque banque;
Banque banque;

Transaction::Transaction(Type type, double montant, const std::string &dateHeure, const std::shared_ptr<Compte> &compteAssocie)
: type(type), montant(montant), dateHeure(dateHeure), compteAssocie(compteAssocie)
{
}

void Transaction::Enregistrer()
{
    std::ofstream transactionsFile("transactions.txt", std::ios_base::app); // Open in append mode

    if (transactionsFile.is_open()) {
        transactionsFile << typeToStr() << ","  
                         << montant << ","
                         << dateHeure << "," 
                         << compteAssocie->getNumeroCompte() << "\n";
        logTransaction("transactions.log", *this);
        transactionsFile.close();
    }  else {
        throw std::runtime_error("Failed to open transactions file for writing.");
    }
}

std::string Transaction::typeToStr() const {
    switch (type) {
        case Type::Depot: return "Depot";
        case Type::Retrait:  return "Retrait";
        case Type::Virement: return "Virement";
    }
}

void Transaction::Annuler() {
    if (type != Type::Retrait) {
        throw std::logic_error("Only withdrawal transactions can be canceled.");
    }

    std::vector<Transaction> allTransactions = readTransactionsFromFile(); 

    // Find the index of the transaction to cancel
    int transactionIndex = -1;
    for (int i = 0; i < allTransactions.size(); ++i) {
        if (allTransactions[i].getCompteAssocie()->getNumeroCompte() == compteAssocie->getNumeroCompte() &&
            allTransactions[i].getMontant() == montant &&
            allTransactions[i].getDateHeure() == dateHeure) {
            transactionIndex = i;
            break;
        }
    }
    if (transactionIndex != -1) {
        allTransactions.erase(allTransactions.begin() + transactionIndex); // Remove the transaction
        writeTransactionsToFile(allTransactions);                        // Overwrite the file
        compteAssocie->Deposer(montant);                               // Update account balance
    } else {
        throw std::runtime_error("Transaction to cancel not found.");
    }
}



// Helper functions to read and write transactions to the file
std::vector<Transaction> readTransactionsFromFile() {
    std::vector<Transaction> transactions;
    std::ifstream file("transactions.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            transactions.push_back(parseTransactionFromLine(line));
        }
        file.close();
    } else {
        throw 
    }

    return transactions;
}

// Helper to parse a line from the CSV file
Transaction parseTransactionFromLine(const std::string& line) {
    std::stringstream ss(line);
    std::string typeStr, montantStr, dateHeureStr, compteNumeroStr;

    std::getline(ss, typeStr, ',');
    std::getline(ss, montantStr, ',');
    std::getline(ss, dateHeureStr, ',');
    std::getline(ss, compteNumeroStr, ','); 

    Transaction::Type type;
    if (typeStr == "Depot") {
        type = Transaction::Type::Depot;
    } else if (typeStr == "Retrait") {
        type = Transaction::Type::Retrait;
    } else if (typeStr == "Virement") {
        type = Transaction::Type::Virement;
    } else {
        throw std::runtime_error("Invalid transaction type encountered: " + typeStr);
    }
        int numeroCompte; 
    try {
        numeroCompte = std::stoi(compteNumeroStr);
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid account number encountered: " + compteNumeroStr);
    }
    double montant = std::stod(montantStr);
    std::string dateHeure = dateHeureStr;
    int compteNumero = std::stoi(compteNumeroStr);

    auto compteAssociePtr = std::make_shared<Compte>(numeroCompte);
    return Transaction(type, montant, dateHeure, compteAssociePtr);
}

void writeTransactionsToFile(const std::vector<Transaction>& transactions) {
    std::ofstream file("transactions.txt");

    if (file.is_open()) {
        for (const auto& transaction : transactions) {
            file << transaction.typeToStr() << ","  
                 << transaction.getMontant() << ","
                 << transaction.getDateHeure() << "," 
                 << transaction.getCompteAssocie()->getNumeroCompte() << "\n"; 
        }
        file.close();
    } else {
        throw std::runtime_error("Failed to open transactions file for writing.");
    }
}

Transaction::Type Transaction::getType() const
{
    return type;
}

double Transaction::getMontant() const
{
    return montant;
}

const std::string& Transaction::getDateHeure() const
{
    return dateHeure;
}

const std::shared_ptr<Compte>& Transaction::getCompteAssocie() const {
    return compteAssocie;
}