#pragma once

#include <string>

class Host {
  public:
    Host(std::string hostId, std::string hostName, std::string hostPort)
        : id_(std::move(hostId)), name_(std::move(hostName)),
          port_(std::move(hostPort)) {};

    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getPort() const;

  private:
    std::string id_;
    std::string name_;
    std::string port_;
};
