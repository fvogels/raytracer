#pragma once

#include "io/binary-reader.h"
#include <memory>
#include <string>


namespace io
{
    std::unique_ptr<BinaryReader> create_file_binary_reader(const std::string& path);
}
