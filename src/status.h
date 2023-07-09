#pragma once

#include <cstring>
#include <iostream>

enum class StatusCode { INVALID = -1, OK = 0, Cancelled = 1, KeyError = 2 };

class Status {
 public:
  Status() : code_(StatusCode::OK) {}
  explicit Status(StatusCode code) : code_(code) {}
  Status(StatusCode code, const std::string& msg) : code_(code), msg_(msg) {}

  StatusCode code() const { return code_; }

  const std::string& message() const { return msg_; }

  bool ok() const { return code_ == StatusCode::OK; }

  static Status OK() { return Status(); }

  static Status Invalid(const std::string& msg) {
    return Status(StatusCode::INVALID, msg);
  }

  static Status Cancelled(const std::string& msg) {
    return Status(StatusCode::Cancelled, msg);
  }

  static Status KeyError(const std::string& msg) {
    return Status(StatusCode::KeyError, msg);
  }

  std::string ToString() const {
    std::string statusString;

    switch (code_) {
      case StatusCode::OK:
        statusString = "OK";
        break;
      case StatusCode::Cancelled:
        statusString = "Cancelled";
        break;
      default:
        statusString = "Unknown";
        break;
    }

    if (!msg_.empty()) {
      statusString += ": " + msg_;
    }

    return statusString;
  }

  void Abort(const std::string& message) const {
    std::cerr << "-- Arrow Fatal Error --\n";
    if (!message.empty()) {
      std::cerr << message << "\n";
    }
    std::cerr << ToString() << std::endl;
    std::abort();
  }

 private:
  StatusCode code_;
  std::string msg_;
};
