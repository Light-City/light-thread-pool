load("@rules_cc//cc:defs.bzl", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_test(
    name = "env_test",
    srcs = ["env_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)
cc_test(
    name = "submit_test",
    srcs = ["submit_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)

cc_test(
    name = "cancel_test",
    srcs = ["cancel_test.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)