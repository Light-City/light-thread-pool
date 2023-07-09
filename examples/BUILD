load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hello_world",
    srcs = ["hello_world.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)

cc_binary(
    name = "submit",
    srcs = ["submit.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)

cc_binary(
    name = "env_spawn",
    srcs = ["env_spawn.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)

cc_binary(
    name = "stop_token",
    srcs = ["stop_token.cc"],
    copts = ["-std=c++17"],
    deps = [
        "//src:thread_pool",
        "@catch2",
    ],
)