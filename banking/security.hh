/**
 * \file security.hh
 * \brief Header for files needed for checking credentials
 */ 
#ifndef SECURITY_HH
#define SECURITY_HH

#include <string>


namespace security {
    /**
     * Hash a password.
     */ 
    std::string superSecretHashFunction(const std::string& password);

    /**
     * Check if a proposed password matches the hash.
     */ 
    bool superSecretCheckHashFunction(const std::string& password, const std::string& passwordHash);
}

#endif