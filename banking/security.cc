#include "security.hh"

const std::string HASH_SUFFIX("_hash");

std::string
security::superSecretHashFunction(const std::string& password) {
    return password + HASH_SUFFIX;
}

bool
security::superSecretCheckHashFunction(const std::string& password, const std::string& passwordHash) {
    // Note that the password "hash" is guaranteed to be longer than the suffix
    // so size_t subtraction won't fail
    if (password == passwordHash.substr(0, passwordHash.size() - HASH_SUFFIX.size())) {
        return true;
    }
    return false;
}
