cc_test(
    name = "highscores_test",
    size = "small",
    srcs = ["highscores_test.cc"],
    copts = ["-Ilib"],
    deps = [
        "//lib:highscores",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "ctf_test",
    size = "small",
    srcs = ["ctf_test.cc"],
    copts = ["-Ilib"],
    deps = [
        "//lib:ctf",
        # "//lib:highscores",
        "@com_google_googletest//:gtest_main",
    ],
)
