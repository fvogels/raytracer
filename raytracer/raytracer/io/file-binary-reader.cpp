#include "io/file-binary-reader.h"
#include "easylogging++.h"


namespace
{
    class FileBinaryReader : public io::BinaryReader
    {
    public:
        FileBinaryReader(const std::string& path) : stream(path, std::ios::binary)
        {
            CHECK(stream) << "Failed to open " << path;
        }

        void read(unsigned byte_count, uint8_t* buffer) override
        {
            stream.read(reinterpret_cast<char*>(buffer), byte_count);
        }

    private:
        std::ifstream stream;
    };
}


std::unique_ptr<io::BinaryReader> io::create_file_binary_reader(const std::string& path)
{
    return std::make_unique<FileBinaryReader>(path);
}