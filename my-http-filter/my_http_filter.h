#pragma once

#include <string>

#include "envoy/server/filter_config.h"

#include "my-http-filter/my_http_filter.pb.h"

#include "extensions/filters/http/common/pass_through_filter.h"

namespace Envoy {
namespace Http {

class HttpSampleFilterConfig {
public:
  HttpSampleFilterConfig(const mysample::MyDecoder& proto_config);

  const std::string& key() const { return key_; }
  const std::string& val() const { return val_; }

private:
  const std::string key_;
  const std::string val_;
};

typedef std::shared_ptr<HttpSampleFilterConfig> HttpSampleFilterConfigSharedPtr;

class HttpSampleFilter : public PassThroughFilter, public Logger::Loggable<Logger::Id::filter> {
public:
  HttpSampleFilter(HttpSampleFilterConfigSharedPtr);
  ~HttpSampleFilter();

  // Http::StreamFilterBase
  void onDestroy() override;

  // Http::StreamDecoderFilter
  FilterHeadersStatus decodeHeaders(RequestHeaderMap&, bool) override;

  // Http::StreamEncoderFilter
  FilterHeadersStatus encodeHeaders(ResponseHeaderMap&, bool) override;

private:
  const HttpSampleFilterConfigSharedPtr config_;

  const LowerCaseString headerKey() const;
  const std::string headerValue() const;
};

} // namespace Http
} // namespace Envoy
