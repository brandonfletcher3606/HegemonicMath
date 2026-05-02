#pragma once

#include <array>
#include <memory>
#include <stdexcept>

namespace Hegemonic
{
    template<class T, std::size_t COUNT>
    class Vector
    {
        using Value           = T;
        using Pointer         = T*;
        using ConstPointer    = const T*;
        using Reference       = T&;
        using ConstReference  = const T&;

        public:
            // Constructors/Deconstructors
            Vector() 
            { 
                std::memset(mVector.data(), 0, sizeof(mVector)); 
            };
            Vector(std::array<T, COUNT> aVector) : mVector(aVector) {};
            Vector(T aArray[COUNT])
            {
                for (int i = 0; i < COUNT; i++)
                {
                    mVector[i] = aArray[i];
                }
            }
            // Vector(stuff, std::allocator)
            Vector(std::initializer_list<T> aList)
            {
                if (aList.size() != COUNT) { throw std::out_of_range("Vector: constructor: initializer list not correct length"); };
                std::size_t count = 0;
                for (auto element : aList)
                {
                    setElement(element, count);
                    count++;
                }
            }
            ~Vector() = default;

            // getters
            std::size_t getSize() const { return mVector.size(); };
            const std::array<T, COUNT>* get() const { return &mVector; };
            std::array<T, COUNT>* get() { return &mVector; };
            Value getMagnitude() const
            {
                T returnValue;
                memset(&returnValue, 0, sizeof(T));
                for (int i = 0; i < getSize(); i++)
                {
                    returnValue += (mVector.at(i)*mVector.at(i));
                }
                return sqrt(returnValue);
            }
            const Vector<T, COUNT> getNormalized() const
            {
                Vector<T, COUNT> returnVector;
                T mag = getMagnitude();
                for (int i = 0; i < getSize(); i++)
                {
                    returnVector.setElement(getElement(i)/mag, i);
                }
                return returnVector;
            }
            Vector<T, COUNT> getNormalized()
            {
                Vector<T, COUNT> returnVector;
                T mag = getMagnitude();
                for (int i = 0; i < getSize(); i++)
                {
                    returnVector.setElement(getElement(i)/mag, i);
                }
                return returnVector;
            }
            ConstReference getElement(std::size_t aIndex) const
            { 
                if (aIndex >= COUNT) { throw std::out_of_range("VECTOR::getElement: index out of range"); };
                return mVector[aIndex];
            };
            Reference getElement(std::size_t aIndex)
            { 
                if (aIndex >= COUNT) { throw std::out_of_range("VECTOR::getElement: index out of range"); };
                return mVector[aIndex];
            };

            // setters
            void setElement(T aValue, std::size_t aIndex)
            {
                mVector.at(aIndex) = aValue;
            }
            void setAll(T aValue)
            {
                mVector.fill(aValue);
            }
            void setNormalized()
            {
                T mag = getMagnitude();
                for (int i = 0; i < getSize(); i++)
                {
                    (*this)[i] = (*this)[i] / mag;
                }
            }

            // overload operators
            Pointer operator()(std::size_t aIndex)
            {
                if (aIndex >= COUNT) { throw std::out_of_range("VECTOR::operator() index out of range"); };
                return &mVector[aIndex];
            }
            ConstPointer operator()(std::size_t aIndex) const
            {
                if (aIndex >= COUNT) { throw std::out_of_range("VECTOR::operator[] index out of range"); };
                return &mVector[aIndex];
            }
            Reference operator[](std::size_t aIndex)
            {
                if (aIndex >= COUNT) { throw std::out_of_range("VECTOR::operator[] index out of range"); };
                return mVector[aIndex];
            }
            ConstReference operator[](std::size_t aIndex) const
            {
                if (aIndex >= COUNT) { throw std::out_of_range("VECTOR::operator[] index out of range"); };
                return getElement(aIndex);
            }

            template<class T>
            struct iterator
            {
                // Properties of iterator
                using Category   = std::forward_iterator_tag;
                using Distance   = std::ptrdiff_t;

                // Shorthands
                using Value      = T;
                using Pointer    = T*;
                using Reference  = T&;

                iterator(Pointer aPtr) : mPtr(aPtr) {}

                // overload operators
                Pointer operator->()
                {
                    return mPtr;
                }
                Reference operator*() const
                {
                    return *mPtr;
                }
                iterator<T> operator++() 
                { 
                    ++mPtr; 
                    return *this;
                };
                iterator<T> operator++(int) 
                {
                    iterator<T> tmp = *this;
                    ++(*this);
                    return tmp;
                };
                iterator<T> operator--() 
                { 
                    --mPtr; 
                    return *this;
                };
                iterator<T> operator--(int) 
                {
                    iterator<T> tmp = *this;
                    --(*this);
                    return tmp;
                };
                friend bool operator==(const iterator<T> &aValue1, const iterator<T> &aValue2)
                {
                    return aValue1.mPtr == aValue2.mPtr;
                }
                friend bool operator!=(const iterator<T> &aValue1, const iterator<T> &aValue2)
                {
                    return aValue1.mPtr != aValue2.mPtr;
                }
                
                private:
                    Pointer mPtr;
            };

            // Iterators functions
            iterator<T> begin()
            {
                return iterator<T>(&mVector.data()[0]);
            };
            iterator<T> end()
            {
                return iterator<T>(&mVector.data()[mVector.size()]);
            };

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

    using Position2di = Vector2i;
    using Position3di = Vector3i;

    template<class T, std::size_t COUNT>
    Vector<T, COUNT> operator+(const Vector<T, COUNT> &aVector1, const T aValue)
    {
        Vector<T, COUNT> returnVector = Vector<T, COUNT>();
        for (int i = 0; i < COUNT; i++)
        {
            returnVector.setElement(aVector1.getElement(i) + aValue, i);
        }
        return returnVector;
    }

    template<class T, std::size_t COUNT>
    Vector<T, COUNT> operator+(const T aValue, const Vector<T, COUNT> &aVector1)
    {
        return aVector1 + aValue;
    }

    template<class T, std::size_t COUNT>
    Vector<T, COUNT> operator-(const Vector<T, COUNT> &aVector1, const T aValue)
    {
        Vector<T, COUNT> returnVector = Vector<T, COUNT>();
        for (int i = 0; i < COUNT; i++)
        {
            returnVector.setElement(aVector1.getElement(i) - aValue, i);
        }
        return returnVector;
    }

    template<class T, std::size_t COUNT>
    Vector<T, COUNT> operator-(const T aValue, const Vector<T, COUNT> &aVector1)
    {
        return aVector1 - aValue;
    }

    template<class T, std::size_t COUNT>
    Vector<T, COUNT> operator+(const Vector<T, COUNT> &aVector1, const Vector<T, COUNT> aVector2)
    {
        Vector<T, COUNT> returnVector = Vector<T, COUNT>();
        for (int i = 0; i < COUNT; i++)
        {
            returnVector.setElement(aVector1.getElement(i) + aVector2.getElement(i), i);
        }
        return returnVector;
    }

    template<class T, std::size_t COUNT>
    Vector<T, COUNT> operator-(const Vector<T, COUNT> &aVector1, const Vector<T, COUNT> aVector2)
    {
        Vector<T, COUNT> returnVector = Vector<T, COUNT>();
        for (int i = 0; i < COUNT; i++)
        {
            returnVector.setElement(aVector1.getElement(i) - aVector2.getElement(i), i);
        }
        return returnVector;
    }
};