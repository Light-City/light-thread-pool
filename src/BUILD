load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])


cc_library(
    name = "thread_pool",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    copts = ["-std=c++17"],
    linkopts = ["-lpthread"],
    visibility = ["//visibility:public"],
)