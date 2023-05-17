load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "7889ba028854b03e0a73d41b2ee6ede4f1a4ab100b18d18bda8488e5d751ba42",
    strip_prefix = "googletest-d6fb5e3bf76c0363d7519373a07c2435e57c1073",
    urls = ["https://github.com/google/googletest/archive/d6fb5e3bf76c0363d7519373a07c2435e57c1073.zip"],
    # urls = ["https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip"],
    # ulrs = ["https://github.com/google/googletest/archive/refs/heads/main.zip"],
)

# below are needed for bazel-watcher
http_archive(
    name = "com_google_absl",
    sha256 = "f88c0030547281e8283ff183db61564ff08d3322a8c2e2de4c40e38c03c69aea",
    strip_prefix = "abseil-cpp-c27ab06897f330267bed99061ed3e523e2606bf1",
    urls = ["https://github.com/abseil/abseil-cpp/archive/c27ab06897f330267bed99061ed3e523e2606bf1.zip"],  # 2022-04-18T19:51:27Z
)

http_archive(
    name = "com_googlesource_code_re2",
    sha256 = "906d0df8ff48f8d3a00a808827f009a840190f404559f649cb8e4d7143255ef9",
    strip_prefix = "re2-a276a8c738735a0fe45a6ee590fe2df69bcf4502",
    urls = ["https://github.com/google/re2/archive/a276a8c738735a0fe45a6ee590fe2df69bcf4502.zip"],  # 2022-04-08
)

http_archive(
    name = "bazel_skylib",
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
)

http_archive(
    name = "platforms",
    sha256 = "b601beaf841244de5c5a50d2b2eddd34839788000fa1be4260ce6603ca0d8eb7",
    strip_prefix = "platforms-98939346da932eef0b54cf808622f5bb0928f00b",
    urls = ["https://github.com/bazelbuild/platforms/archive/98939346da932eef0b54cf808622f5bb0928f00b.zip"],
)
