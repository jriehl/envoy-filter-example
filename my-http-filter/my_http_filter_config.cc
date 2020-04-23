#include <string>

#include "envoy/registry/registry.h"

#include "my-http-filter/my_http_filter.pb.h"
#include "my-http-filter/my_http_filter.pb.validate.h"
#include "my_http_filter.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class HttpSampleDecoderFilterConfig : public NamedHttpFilterConfigFactory {
public:
  Http::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                     const std::string&,
                                                     FactoryContext& context) override {

    return createFilter(Envoy::MessageUtil::downcastAndValidate<const mysample::MyDecoder&>(
                            proto_config, context.messageValidationVisitor()),
                        context);
  }

  /**
   *  Return the Protobuf Message that represents your config incase you have config proto
   */
  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new mysample::MyDecoder()};
  }

  std::string name() const override { return "mysample"; }

private:
  Http::FilterFactoryCb createFilter(const mysample::MyDecoder& proto_config, FactoryContext&) {
    Http::HttpSampleDecoderFilterConfigSharedPtr config =
        std::make_shared<Http::HttpSampleDecoderFilterConfig>(
            Http::HttpSampleDecoderFilterConfig(proto_config));

    return [config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      auto filter = new Http::HttpSampleDecoderFilter(config);
      callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{filter});
    };
  }
};

/**
 * Static registration for this sample filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<HttpSampleDecoderFilterConfig, NamedHttpFilterConfigFactory>
    register_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy
