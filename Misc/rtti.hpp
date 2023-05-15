#pragma once

#include <string>

namespace flat::misc::rtti
{
    template <typename T>
    struct TypeID
    {
        static long long get()
        {
            static long long id = reinterpret_cast<long long>(&id);
            return id;
        }
    };

    /*
        how to use:

        struct A
        {
            long long get_rtti_id()
            {
                static long long id = TypeID<A>::get();
                return id;
            }
        };

        struct B
        {
            long long get_rtti_id()
            {
                static long long id = TypeID<B>::get();
                return id;
            }
        };

        then compare directly:
        std::cout << A().get_rtti_id() == B().get_trri_id() << std::endl;

        this RTTI impl won't go through vtable, it will run faster than typeid()
        however when using this impl on a virtual inherted system, it will be slower than typeid()
        this is because function get_rtti_id() must be virtual so you won't call the wrong version of this function
        this brings the same cost that typeid() do
    */
}