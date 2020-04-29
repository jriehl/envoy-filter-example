#include <string>

#include "envoy/http/filter.h"
#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"

#include "empty_http_filter_config.h"
#include "extensions/filters/http/common/pass_through_filter.h"

namespace Envoy {
namespace Http {

class DataTraceLogger : public PassThroughFilter, public Logger::Loggable<Logger::Id::filter> {
public:
    FilterDataStatus decodeData(Buffer::Instance& data, bool end_stream) {
        if (!end_stream) {
            auto& active_span = decoder_callbacks_->activeSpan();
            auto data_str = data.toString();
            /*  The current Zipkin trace reporter ignores logs.  I can verify the
                log message is being stored in the span, and that the serializer
                ignores log "annotations" completely.  So functionally, the
                following line does nothing. */
            active_span.log(std::chrono::system_clock::now(), "decodedData");
            active_span.setTag("request_data", data_str);
            ENVOY_LOG(debug, "decodeData(): {}", data_str);
        }
        return FilterDataStatus::Continue;
    }

    FilterDataStatus encodeData(Buffer::Instance& data, bool end_stream) {
        if (!end_stream) {
            auto& active_span = encoder_callbacks_->activeSpan();
            auto data_str = data.toString();
            active_span.log(std::chrono::system_clock::now(), "encodedData");
            active_span.setTag("response_data", data_str);
            ENVOY_LOG(debug, "encodeData(): {}", data_str);
        }
        return FilterDataStatus::Continue;
    }
};

class DataTraceLoggerConfig : public Extensions::HttpFilters::Common::EmptyHttpFilterConfig {
public:
    DataTraceLoggerConfig() : EmptyHttpFilterConfig("data_trace_logger") {}

    FilterFactoryCb createFilter(const std::string&, Server::Configuration::FactoryContext&) {
        return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
            callbacks.addStreamFilter(std::make_shared<DataTraceLogger>());
        };
    }
};

static Registry::RegisterFactory<DataTraceLoggerConfig, DataTraceLoggerConfig::NamedHttpFilterConfigFactory>
    register_;

} // namespace Http
} // namespace Envoy
