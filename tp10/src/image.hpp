#pragma once

#include <cstddef>
#include <array>
#include <functional>

template<typename P, size_t W, size_t H>
class Image {
    public:
    Image() = default;
    Image(const P& pixel) {
        for (auto& ligne : _image) {
            ligne.fill(pixel);
        }
    }

    const P& operator()(int i, int j) const {
        return _image[j][i];
    }

    P& operator()(int i, int j) {
        return _image[j][i];
    }
    
    Image<P, W, H> operator+(const Image<P, W, H>& other) {
        auto result = Image();
        for (size_t i = 0; i < W; i++) {
            for (size_t j = 0; j < H; j++) {
                result(j, i) = (*this)(j, i) + other(j, i);
            }
        }
        return result;
    }    

    Image<P, W, H>(const std::function<P(size_t i, size_t j)>& functeur) {
        for (size_t h = 0; h < H; ++h) {
            for (size_t w = 0; w < W; ++w) {
                (*this)(w, h) = functeur(w, h);
            }
        }
    }

    private:
    std::array<std::array<P, W>, H> _image;
};