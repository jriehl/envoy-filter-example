Originates from the following:
https://github.com/sarvij10/envoy-filter-example/tree/modify_response/myfilters/modify_buffer

Manual demo and test procedure:
* Start up some containers in Docker:
    - `docker run -d -p 8088:80 nginx:latest`
    - `docker run -d -p 9411:9411 -p 16686:16686 jaegertracing/all-in-one`
* Build and run custom Envoy:
    - `bazel build //data-trace-logger:envoy`
    - `bazel-bin/data-trace-loggger/envoy -c data-trace-logger/data_trace_logger.yaml`
* Send traffic to Envoy:
    - `curl -v http://127.0.0.1:8080/`
* Check the traces in Jaeger.
    - `open http://127.0.0.1:16686`
