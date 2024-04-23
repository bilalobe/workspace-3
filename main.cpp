#include <iostream>
#include <string> // for getline() functions

#include "banque.h" 
#include "menu.h" 
#include "client.h"
#include "compte.h"
#include "transaction.h"
#include "client.cpp"
#include "compte.cpp"
#include "transaction.cpp"

#include "banque.cpp" 
#include "pret.cpp" 
#include "pret.h"

// Driver code to test the program
using namespace std;


int main() {
    // Create the GestionnaireBanque object
    GestionnaireBanque banque;  

    // Create a Menu object, passing the reference to the bank
    Menu menu(banque);
    
    // Start by displaying the main menu
    menu.afficherMenuPrincipal(); 

    return 0;
}
