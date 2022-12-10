#include <examples/dist.registry.replication/src/domains/register/application/queries/replica/read_register_query_handler.hpp>
#include <examples/dist.registry.replication/src/domains/register/presentation/controllers/replica/read_register_handler.hpp>
#include <examples/dist.registry.replication/src/domains/register/presentation/exception.hpp>

#include <nlohmann/json.hpp>

namespace dsac::presentation::replica {

using application::query::replica::read_register_query;
using application::query::replica::read_register_query_handler;
using application::query::replica::register_state_dto;

namespace {

auto make_response(register_state_dto const& register_state_dto) -> nlohmann::json {
  nlohmann::json response;
  response["value"]     = register_state_dto.get_value();
  response["timestamp"] = register_state_dto.get_timestamp();
  return response;
}

}  // namespace

auto read_register_handler::handle([[maybe_unused]] nlohmann::json const& request) -> nlohmann::json {
  std::optional const register_state_dto = read_register_query_handler::handle(read_register_query{});
  if (!register_state_dto.has_value()) [[unlikely]] {
    throw not_found{"The register is not initialized"};
  }

  return make_response(register_state_dto.value());
}

}  // namespace dsac::presentation::replica
