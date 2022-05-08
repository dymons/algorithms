#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <string_view>

#include <fmt/format.h>

namespace {

constexpr const int kPort       = 8080;
constexpr const int kBufferSize = 2048;

using descriptor   = int;
using message      = std::string;
using message_view = std::string_view;

enum class status : unsigned char { ok, error };
[[nodiscard]] status sent_message(descriptor const descriptor, message const& data) {
  long const bytes = write(descriptor, data.data(), data.size());
  return bytes < 0 ? status::error : status::ok;
}

struct request {
  status  code;
  message payload;
};
[[nodiscard]] request receive_message(descriptor const descriptor) {
  request    request{.code = status::ok, .payload = message(kBufferSize, '0')};
  long const bytes = read(descriptor, request.payload.data(), request.payload.size());
  if (bytes <= 0) {
    request.code = status::error;
    request.payload.clear();
    request.payload.shrink_to_fit();
    return request;
  }

  request.payload.resize(bytes);
  return request;
}

[[nodiscard]] message make_http_response(message_view const payload) {
  return fmt::format("HTTP/1.1 200 OK\nContent-Length: {}\n\n{}", payload.size(), payload);
}

[[nodiscard]] message get_payload_from_request(message const& data) {
  std::size_t const payload_start = data.find_last_of("\n\n", data.find_last_of("\n\n"));
  if (payload_start != message::npos) {
    return data.substr(payload_start + 1U, data.size() - payload_start);
  }

  return {};
}

int start_handling_requests_on_socket(descriptor const listen_socket) {
  fd_set active_sockets;
  FD_ZERO(&active_sockets);
  FD_SET(listen_socket, &active_sockets);

  while (true) {
    fd_set snapshot_sockets = active_sockets;
    if (select(FD_SETSIZE, &snapshot_sockets, nullptr, nullptr, nullptr) < 0) {
      break;
    }

    for (descriptor socket{}; socket < FD_SETSIZE; ++socket) {
      if (!FD_ISSET(socket, &snapshot_sockets)) {
        continue;
      }

      if (socket == listen_socket) {
        sockaddr_in client_socket_description{};
        socklen_t   size = sizeof(client_socket_description);
        descriptor  new_connection_descriptor =
            accept(listen_socket, reinterpret_cast<sockaddr*>(&client_socket_description), &size);
        if (new_connection_descriptor < 0) {
          break;
        }

        FD_SET(new_connection_descriptor, &active_sockets);
      } else {
        if (request const request = receive_message(socket); request.code == status::error) {
          close(socket);
          FD_CLR(socket, &active_sockets);
        } else {
          message const payload = get_payload_from_request(request.payload);
          if (sent_message(socket, make_http_response(payload)) == status::error) {
            close(socket);
            FD_CLR(socket, &active_sockets);
          }
        }
      }
    }
  }

  close(listen_socket);

  return 0;
}
}  // namespace

int main() {
  constexpr const int kUseTcp       = 0;
  descriptor const    listen_socket = socket(PF_INET, SOCK_STREAM, kUseTcp);
  if (listen_socket < 0) {
    std::cout << "listen socket was not created" << std::endl;
    return 1;
  }

  int opt = 1;
  setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt));

  sockaddr_in sock_description{};
  sock_description.sin_family      = AF_INET;
  sock_description.sin_port        = htons(kPort);
  sock_description.sin_addr.s_addr = htonl(INADDR_ANY);
  int const error_bind = bind(listen_socket, reinterpret_cast<sockaddr*>(&sock_description), sizeof(sock_description));
  if (error_bind < 0) {
    std::cout << "Failed to bind a socket" << std::endl;
    return 1;
  }

  constexpr const int kSizeQueue = 3;
  if (int const error = listen(listen_socket, kSizeQueue); error < 0) {
    std::cout << "Listen queue failure" << std::endl;
    return 1;
  }

  return start_handling_requests_on_socket(listen_socket);
}
