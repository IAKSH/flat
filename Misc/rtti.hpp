#pragma once

#include <string>

namespace flat::misc::rtti
{
    template <typename T>
    struct TypeID
    {
        static std::string get()
        {
            static std::string id = std::to_string(reinterpret_cast<long long>(&id));
            return id;
        }
    };

    /*
        how to use:

        struct Base
        {
            static std::string_view get_rtti_id()
            {
                static std::string id = TypeID<Base>::get();
                return id;
            }
        };

        struct Derived : public Base
        {
            static std::string_view get_rtti_id()
            {
                static std::string id = TypeID<Derived>::get();
                return id;
            }
        };

        then compare directly:
        std::cout << Base().get_rtti_id() == Derived().get_trri_id() << std::endl;

        this RTTI impl won't take vtable into consideration, so it should be faster then typeid()
    */
}