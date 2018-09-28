
#pragma once
#ifdef _MSC_VER
#include <intrin.h>
#include <stdexcept>

#else

#include <x86intrin.h>

#endif


#include "hnswlib.h"

namespace hnswlib {

    static unsigned long long
    hamming(const void *pVect1, const void *pVect2, const void *qty_ptr) {
        size_t qty = *((size_t *) qty_ptr);
        unsigned long long res = 0;
        for (unsigned i = 0; i < qty; i++) {
            int t = __builtin_popcountll(
                ((unsigned long long *) pVect1)[i] ^ ((unsigned long long *) pVect2)[i]
            );
            res += t;
        }
        return (res);

    };

    class HammingSpace : public SpaceInterface<unsigned long long> {

        DISTFUNC<unsigned long long> fstdistfunc_;
        size_t data_size_;
        size_t dim_;
    public:
        HammingSpace(size_t dim) {
            fstdistfunc_ = hamming;
            dim_ = dim;
            data_size_ = dim * sizeof(unsigned long long);
        }

        size_t get_data_size() {
            return data_size_;
        }

        DISTFUNC<unsigned long long> get_dist_func() {
            return fstdistfunc_;
        }

        void *get_dist_func_param() {
            return &dim_;
        }

    };


};
