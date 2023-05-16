cc_test(
    name = "highscores_test",
    size = "small",
    srcs = ["highscores_test.cc"],
    deps = [
        "//src:highscores",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "ctf_test",
    size = "small",
    srcs = ["ctf_test.cc"],
    deps = [
        "//src:ctf",
        "//src:highscores",
        "@com_google_googletest//:gtest_main",
    ],
)
