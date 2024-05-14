#ifndef LOGGING_UTILS_H
#define LOGGING_UTILS_H

#include "transaction.h"
#include "pret.h"
#include <ctime>
#include <chrono>

std::string getCurrentDateTime();

void logTransaction(const std::string& filename, const Transaction& transaction);

#endif