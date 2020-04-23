package(default_visibility = ["//visibility:public"])

load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_library",
    "envoy_cc_test",
)

load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

envoy_cc_binary(
    name = "envoy",
    repository = "@envoy",
    deps = [
        ":my_http_filter_config",
        "@envoy//source/exe:envoy_main_entry_lib",
    ],
)

api_proto_package()

envoy_cc_library(
    name = "my_http_filter_lib",
    srcs = ["my_http_filter.cc"],
    hdrs = ["my_http_filter.h"],
    repository = "@envoy",
    deps = [
        ":pkg_cc_proto",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "my_http_filter_config",
    srcs = ["my_http_filter_config.cc"],
    repository = "@envoy",
    deps = [
        ":my_http_filter_lib",
        "@envoy//include/envoy/server:filter_config_interface",
    ],
)

envoy_cc_test(
    name = "my_http_filter_integration_test",
    srcs = ["my_http_filter_integration_test.cc"],
    repository = "@envoy",
    deps = [
        ":my_http_filter_config",
        "@envoy//test/integration:http_integration_lib",
    ],
)
