cc_library(
    name = "printer",
    srcs = ["printer.c"],
    hdrs = ["printer.h"],
    copts = [
        "-std=c11",
        "-Ilib",
    ],
    # visibility = ["//visibility:private"],
    deps = ["//lib:highscores"],
)

cc_binary(
    name = "main",
    srcs = ["main.c"],
    copts = [
        "-std=c11",
        "-Ilib",
    ],
    deps = [
        ":printer",
        "//lib:ctf",
    ],
)
