#pragma once

#include <array>
#include <memory>
#include <stdexcept>

namespace Hegemonic
{
    template<class T, std::size_t COUNT>
    class Vector
    {
        public:
            Vector() { std::memset(mVector.data(), 0, sizeof(mVector)); };
            Vector(std::array<T, COUNT> aVector) { mVector = aVector; };
            Vector(T aArray[COUNT])
            {
                for (int i = 0; i < COUNT; i++)
                {
                    mVector[i] = aArray[i];
                }
            }
            ~Vector() = default;

            // getters
            std::size_t getSize() const { return mVector.size(); };
            std::array<T, COUNT> get() const { return mVector; };
            T getMagnitude() const
            {
                T returnValue;
                memset(&returnValue, 0, sizeof(T));
                for (int i = 0; i < getSize(); i++)
                {
                    returnValue += (mVector.at(i)*mVector.at(i));
                }
                return sqrt(returnValue);
            }
            T getElement(std::size_t aIndex) const 
            { 
                return mVector.at(aIndex);
            };

            // setters
            void setElement(T aValue, std::size_t aIndex)
            {
                mVector.at(aIndex) = aValue;
            }

        private:
            std::array<T, COUNT> mVector;
    };

    template<class T>
    using Vector2 = Vector<T, 2>;

    template<class T>
    using Vector3 = Vector<T, 3>;

    template<class T>
    using Vector4 = Vector<T, 4>;

    using Vector2d = Vector2<double>;
    using Vector2i = Vector2<int>;
    using Vector3d = Vector3<double>;
    using Vector3i = Vector3<int>;
    using Vector4d = Vector4<double>;
    using Vector4i = Vector4<int>;
};