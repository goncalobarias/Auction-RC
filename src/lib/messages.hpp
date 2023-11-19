#ifndef __MESSAGES_HPP__
#define __MESSAGES_HPP__

#include "constants.hpp"

#define DEFAULT_AS_HOST_STR                                                    \
    "[INFO] Could not find ASIP address, using default host: "                 \
        << DEFAULT_AS_HOST
#define DEFAULT_AS_PORT_STR                                                    \
    "[INFO] Could not find ASport number, using default port: "                \
        << DEFAULT_AS_PORT
#define SHUTDOWN_STR "Closing the user application..."

#define GETADDRINFO_UDP_ERR "[ERR] Failed to get address for UDP connection: "
#define GETADDRINFO_TCP_ERR "[ERR] Failed to get address for TCP connection: "
#define SOCKET_CREATE_ERR "[ERR] Failed to create socket."
#define SOCKET_CLOSE_ERR "[ERR] Failed to close socket."
#define SOCKET_TIMEOUT_ERR "[ERR] Failed to set socket timeout."
#define PORT_ERR "[ERR] Invalid port number."
#define READING_ERR "[ERR] An unexpected error occured while reading a string."
#define SIGACTION_ERR "[ERR] Failed to set signal action."

#define UNEXPECTED_COMMAND_ERR(commandName)                                    \
    "[ERR] The command '" << commandName                                       \
                          << "' is not supported by this application."
#define PACKET_ERR "[ERR] An error occured with the packet. Please try again."
#define LOGIN_ERR                                                              \
    "A user is already logged in. To log into another account, please log "    \
    "out first."
#define UID_ERR "Invalid user ID. Expected a 6 digit positive number."
#define PASSWORD_ERR "Invalid password. Expected 8 alphanumeric characters."
#define LOGIN_OK "Logged in successfully."
#define LOGIN_NOK(user) "Incorrect password for user '" << user << "'."
#define LOGIN_REG(user) "New user '" << user << "' registered and logged in."
#define LOGOUT_OK "Logged out successfully."
#define UNREG_OK(user) "Successfully unregistered the user '" << user << "'."
#define NO_LOGIN "No user is currently logged in."
#define NO_REG(user) "User '" << user << "' is not registered."
#define EXIT_ERR                                                               \
    "A user is still logged in, please make sure to logout before exitting "   \
    "the application."

#endif // __MESSAGES_HPP__
