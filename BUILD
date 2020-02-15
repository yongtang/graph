licenses(["notice"])  # Apache 2.0

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "demo",
    srcs = [
        "demo.cc",
    ],
    copts = [
        "-std=c++14",
    ],
    linkopts = [
        "-framework",
        "Metal",
        "-framework",
        "Cocoa",
        "-framework",
        "CoreVideo",
    ],
    linkstatic = True,
    deps = select({
        "@bazel_tools//src/conditions:darwin": [
            "@filament_mac//:filament",
        ],
        "//conditions:default": [],
    }),
)
