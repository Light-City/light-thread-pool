#pragma once
#include <iostream>
#include <optional>

#include "status.h"
#include "visibility.h"
ARROW_EXPORT
std::optional<std::string> GetEnvVar(const char* name);
ARROW_EXPORT
Status SetEnvVar(const char* name, const char* value);
ARROW_EXPORT
Status SetEnvVar(const std::string& name, const std::string& value);