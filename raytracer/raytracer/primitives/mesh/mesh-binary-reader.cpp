#include "primitives/mesh/mesh-binary-reader.h"
#include <cstdint>
#include <fstream>
#include <memory>
#include "easylogging++.h"


using namespace raytracer;


namespace
{
    class Reader
    {
    private:
        void* pointer;

    public:
        Reader(void* pointer)
            : pointer(pointer)
        {
            // NOP
        }

        template<typename T>
        T read()
        {
            T* p = reinterpret_cast<T*>(pointer);
            T value = *p;
            pointer = reinterpret_cast<void*>(p + 1);

            return value;
        }
    };

    void read_vertices(Reader& reader, raytracer::primitives::MeshReceiver& receiver, unsigned n_vertices)
    {
        LOG(INFO) << "Reading " << n_vertices << " vertices";

        for (unsigned i = 0; i != n_vertices; ++i)
        {
            double x = reader.read<double>();
            double y = reader.read<double>();
            double z = reader.read<double>();

            receiver.vertex(x, y, z);
        }
    }

    void read_normals(Reader& reader, raytracer::primitives::MeshReceiver& receiver, unsigned n_normals)
    {
        LOG(INFO) << "Reading " << n_normals << " normals";

        for (unsigned i = 0; i != n_normals; ++i)
        {
            double x = reader.read<double>();
            double y = reader.read<double>();
            double z = reader.read<double>();

            receiver.normal(x, y, z);
        }
    }

    void read_hierarchy(Reader& reader, raytracer::primitives::MeshReceiver& receiver)
    {
        LOG(INFO) << "Reading hierarchy";

        while (true)
        {
            auto tag = reader.read<uint32_t>();

            if (tag == 0)
            {
                auto n = reader.read<uint32_t>();

                receiver.box(n);
            }
            else if (tag == 1)
            {
                auto i = reader.read<uint32_t>();
                auto j = reader.read<uint32_t>();
                auto k = reader.read<uint32_t>();

                receiver.triangle(i, j, k);
            }
            else if (tag == 0xFFFFFFFF)
            {
                break;
            }
            else
            {
                LOG(ERROR) << "Unrecognized tag \"" << tag << "\"" << std::endl;
                abort();
            }
        }
    }
}

void raytracer::primitives::read_binary_mesh(std::istream& input_stream, raytracer::primitives::MeshReceiver& receiver)
{
    TIMED_FUNC(timerObj);
    LOG(INFO) << "Loading binary mesh...";

    input_stream.seekg(0, std::ios::end);
    auto size = input_stream.tellg();
    input_stream.seekg(0, std::ios::beg);

    static_assert(sizeof(char) == 1, "char must have size 1");

    std::unique_ptr<char[]> buffer(new char[size]);
    input_stream.read(buffer.get(), size);
    Reader reader(buffer.get());

    auto n_vertices = reader.read<uint32_t>();
    auto n_normals = reader.read<uint32_t>();

    read_vertices(reader, receiver, n_vertices);
    read_normals(reader, receiver, n_normals);
    read_hierarchy(reader, receiver);
}