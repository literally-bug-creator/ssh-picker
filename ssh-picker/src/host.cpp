#include "host.hpp"

#include <string>

const std::string& Host::getId() const {
    return id_;
}

const std::string& Host::getName() const {
    return name_;
}

const std::string& Host::getPort() const {
    return port_;
}
