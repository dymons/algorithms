#include <examples/dist.registry.replication/src/domains/register/presentation/controllers/replica/read_register_handler.hpp>
#include <examples/dist.registry.replication/src/domains/register/presentation/controllers/replica/write_register_handler.hpp>
#include <examples/dist.registry.replication/src/domains/register/presentation/exception.hpp>
#include <examples/dist.registry.replication/src/domains/register/presentation/web/detail/httplib.hpp>
#include <examples/dist.registry.replication/src/domains/register/presentation/web/register_replica_client.hpp>

#include <nlohmann/json.hpp>

namespace dsac::presentation::web {

using presentation::replica::read_register_handler;
using presentation::replica::write_register_handler;

namespace {

const std::string kRequestEmpty = "";

auto to_json(domain::register_dto const& request) -> std::string {
  nlohmann::json request_json;
  request_json["value"]     = request.get_value();
  request_json["timestamp"] = request.get_timestamp();
  return to_string(request_json);
}

auto from_json(nlohmann::json const& json) -> domain::register_dto {
  if (!json.contains("value") || !json["value"].is_number_integer()) [[unlikely]] {
    throw invalid_argument{"Input data is incorrect or the required field 'value' is missing"};
  }
  if (!json.contains("timestamp") || !json["timestamp"].is_number_unsigned()) [[unlikely]] {
    throw invalid_argument{"Input data is incorrect or the required field 'timestamp' is missing"};
  }

  return domain::register_dto::hydrate(json["value"].get<std::int32_t>(), json["timestamp"].get<std::size_t>());
}

}  // namespace

auto register_replica_client::write(domain::register_dto const& request) -> void {
  [[maybe_unused]] httplib::Result const response = httplib::Client{get_host(), get_port()}.Post(
      write_register_handler::get_type_name(), to_json(request), "text/json");
}

auto register_replica_client::read() -> std::optional<domain::register_dto> {
  httplib::Result const response =
      httplib::Client{get_host(), get_port()}.Post(read_register_handler::get_type_name(), kRequestEmpty, "text/json");
  if (!response) {
    throw service_unavailable{fmt::format("Failed to execute the request to host={}, port={}", get_host(), get_port())};
  }

  nlohmann::json const response_json = nlohmann::json::parse(response.value().body);
  return from_json(response_json);
}

}  // namespace dsac::presentation::web
