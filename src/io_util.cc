#include "io_util.h"

std::optional<std::string> GetEnvVar(const char* name) {
  char* c_str = getenv(name);
  if (c_str == nullptr) {
    return {};
  }
  return std::string(c_str);
}

Status SetEnvVar(const char* name, const char* value) {
  if (setenv(name, value, 1) == 0) {
    return Status::OK();
  } else {
    return Status::Invalid("failed setting environment variable");
  }
}

Status SetEnvVar(const std::string& name, const std::string& value) {
  return SetEnvVar(name.c_str(), value.c_str());
}
