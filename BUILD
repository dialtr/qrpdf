load("@rules_cc//cc:defs.bzl", "cc_test", "cc_library", "cc_binary")

cc_library(
    name = "qrencode",
    linkopts = ["-lqrencode"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cairo",
    linkopts = ["-lcairo"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "qrpdf",
    srcs = ["main.cc"],
    deps = [
        ":cairo",
        ":qrencode",
    ],
)
