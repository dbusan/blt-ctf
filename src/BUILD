cc_library(
    name = "highscores",
    srcs = ["highscores.c"],
    hdrs = ["highscores.h"],
    copts = ["-std=c11"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ctf",
    srcs = ["ctf.c"],
    hdrs = ["ctf.h"],
    copts = ["-std=c11"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "main",
    srcs = ["main.c"],
    copts = ["-std=c11"],
    deps = [":highscores"],
)
