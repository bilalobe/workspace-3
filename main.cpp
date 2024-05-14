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


GestionnaireBanque banque; // Global banque object

int main() {
    afficherMenuPrincipal();
    return 0;
}