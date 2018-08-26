#include "exception.h"

SDLException::SDLException(const std::string& msg)
    : std::runtime_error(msg) {}

SDLException::~SDLException() noexcept = default;
