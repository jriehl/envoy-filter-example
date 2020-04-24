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
            ENVOY_LOG(info, "decodeData(): {}", data.toString());
        }
        return FilterDataStatus::Continue;
    }

    FilterDataStatus encodeData(Buffer::Instance& data, bool end_stream) {
        if (!end_stream) {
            ENVOY_LOG(info, "encodeData(): {}", data.toString());
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
