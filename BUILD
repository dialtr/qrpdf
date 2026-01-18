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
