#ifndef LOGGING_UTILS_H
#define LOGGING_UTILS_H

#include "transaction.h"
#include "pret.h"
// ... other includes as needed ...

void logTransaction(const std::string& filename, const Transaction& transaction);

#endif