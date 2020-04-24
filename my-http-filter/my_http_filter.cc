#include <string>

#include "my_http_filter.h"

#include "envoy/server/filter_config.h"

namespace Envoy {
namespace Http {

HttpSampleFilterConfig::HttpSampleFilterConfig(
    const mysample::MyDecoder& proto_config)
    : key_(proto_config.mykey()), val_(proto_config.myval()) {}

HttpSampleFilter::HttpSampleFilter(HttpSampleFilterConfigSharedPtr config)
    : config_(config) {}

HttpSampleFilter::~HttpSampleFilter() {}

void HttpSampleFilter::onDestroy() {}

const LowerCaseString HttpSampleFilter::headerKey() const {
  return LowerCaseString(config_->key());
}

const std::string HttpSampleFilter::headerValue() const {
  return config_->val();
}

FilterHeadersStatus HttpSampleFilter::decodeHeaders(RequestHeaderMap& headers, bool) {
  ENVOY_LOG(info, "INSIDE THE DECODER EXTENSION...");
  // add a header
  headers.addCopy(headerKey(), headerValue());

  return FilterHeadersStatus::Continue;
}

FilterHeadersStatus HttpSampleFilter::encodeHeaders(ResponseHeaderMap& headers, bool) {
  ENVOY_LOG(info, "INSIDE THE ENCODER EXTENSION...");
  headers.addCopy(headerKey(), headerValue());
  return FilterHeadersStatus::Continue;
}

} // namespace Http
} // namespace Envoy
