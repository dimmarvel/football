#include <yas/serialize.hpp>
#include <yas/std_types.hpp>
#include <strstream>

#define SERIALIZABLE_OBJ(...) \
        template<typename Ar> \
        void serialize(Ar &ar) { \
            ar & YAS_OBJECT(nullptr, __VA_ARGS__); \
        } 

#define CONVERTION_IMPL() std::string to_json() const { return fb::core::to_json(*this); }

namespace fb::core
{
    template<typename _Obj>
    inline std::string to_json(const _Obj& obj)
    {
        yas::mem_ostream os;
        yas::save<yas::mem|yas::json|yas::compacted>(os, obj);
        yas::intrusive_buffer buf = os.get_intrusive_buffer();
        return std::string(buf.data, buf.size);
    }
    template<typename _Obj>
    inline _Obj from_json(const std::string& buf)
    {
        _Obj obj;
        std::istrstream is(buf.data(), buf.size());
        yas::std_istream_adapter ia(is);
        yas::load<yas::file|yas::json|yas::compacted>(ia, obj);
        return obj;
    }
}