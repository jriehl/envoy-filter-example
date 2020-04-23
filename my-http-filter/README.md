## Building

To build the Envoy static binary:

1. `git submodule update --init`
2. `bazel build //my-http-filter-example:envoy`

## Testing

To run the `sample` integration test:

`bazel test //my-http-filter-example:my_http_filter_integration_test`
