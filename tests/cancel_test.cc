#define CATCH_CONFIG_MAIN
#include <iostream>

#include "catch.hpp"
#include "src/cancel.h"
#include "src/status.h"

TEST_CASE("Cancel stop", "[token]") {
  WHEN("submit without params or params") {
    arrow::StopSource source;
    arrow::StopToken token = source.token();
    REQUIRE(!token.IsStopRequested());
    REQUIRE(token.Poll().ok());

    source.RequestStop();
    REQUIRE(token.IsStopRequested());
    REQUIRE(StatusCode::Cancelled == token.Poll().code());
  }
}