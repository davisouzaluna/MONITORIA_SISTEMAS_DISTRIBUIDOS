add_executable(client_https https_client.c)

find_package(OpenSSL REQUIRED)

target_link_libraries(client_https OpenSSL::SSL OpenSSL::Crypto)

#debug
#target_compile_options(client_https PRIVATE -Wall -Wextra -Wpedantic)