//
//  Vector.hpp
//  Vector
//
//  Created by WangHao on 2/5/15.
//  Copyright (c) 2015 WangHao. All rights reserved.
//
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace cop4530;

template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v)
{
    for (int i=0;i!=v.size();++i)
    {
        os << v[i]<<' ';
    }
    return os;
}

template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> &rhs)
{
    if (lhs.size()!=rhs.size())
         return false;
    else
    {
        int j=0;int i=0;
        for(;i!=lhs.size();++i)
            {
            if (lhs[i]==rhs[i])
                ++j;
            }
        return (i==j);
    }
}


template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs)
{
    return (!(lhs==rhs));
}

template <typename T>
Vector<T>::Vector(): theSize(0), theCapacity(0)
{
    array = new T[theCapacity];
}
template <typename T>
Vector<T>::Vector(const Vector &rhs):theSize(rhs.theSize),
theCapacity(rhs.theCapacity), array(nullptr)
{
    array = new T[theCapacity];
    for (int k=0;k<rhs.theSize;++k)
    {    array[k] = rhs.array[k];}
}

template <typename T>
const Vector<T>& Vector<T>::operator= (const Vector &rhs)
{
    Vector<T> copy = rhs;
    std::swap(copy,*this);
    return *this;
}
template <typename T>
Vector<T>:: Vector(Vector &&rhs):theSize(rhs.size()),
                   theCapacity(rhs.capacity()), array(nullptr)
{
    swap(array,rhs.array);
    rhs.theSize = 0;
    rhs.theCapacity =0;
}

template <typename T>
Vector<T> & Vector<T>::operator=(Vector &&rhs)
{
    std::swap(theSize,rhs.theSize);
    std::swap(theCapacity,rhs.theCapacity);
    std::swap(array,rhs.array);
}

template <typename T>
Vector<T>::Vector(int num, const T& val):theSize(num),theCapacity(num)
{
    array = new T[theCapacity];
    for (int i=0;i<theSize;++i)
        {array[i]=val;}
}
 template <typename T>
 Vector<T>::Vector(const_iterator start, const_iterator end)
 {
     theSize=0;
     array = new T[theSize];
     auto itr=start;

     for(;itr!=end;++itr)
        { push_back( *itr);}
 }

template <typename T>
Vector<T>::~Vector()
{
    delete [] array;
}

template <typename T>
void Vector<T>::push_back(const T & val)
{
    if (theSize==theCapacity)
        reserve(50*theCapacity+1);
    array[theSize++]=val;
}

template <typename T>
int Vector<T>::size() const
{
    return theSize;
}
template <typename T>
int Vector<T>::capacity() const
{
    return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const
{
    return (theSize==0);
}

template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const
{
    for (int i=0;i<theSize;++i)
    {
        os<<array[i]<<ofc;
    }
}

template <typename T>
T& Vector<T>::operator[](int index)
{
    return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const
{
    return array[index];
}

template <typename T>
void Vector<T>::doubleCapacity()
{
if (theCapacity==0)
   { theCapacity = 1;}
else
   { reserve(theCapacity*2);}
}

template <typename T>
void Vector<T>::reserve(int newCapacity)
{
    if (newCapacity>theSize)
    {
        T* temp = new T[newCapacity];
        for (int i=0;i<theSize;++i)
           { temp[i]=std::move(array[i]);}
        theCapacity = newCapacity;
        std::swap(temp,array);
        delete []temp;
    }
}

template <typename T>
T& Vector<T>::at(int loc )           
{
    if (loc>theSize||loc<0)               
        throw out_of_range("error");
    else
        return array[loc];
}

template <typename T>
const T& Vector<T>::at(int loc ) const
{
    if (loc>theSize||loc<0)
        throw out_of_range("error");
    else
        return array[loc];
}
T & Vector<T>::front()
{
    return array[0];
}

template <typename T>
const T& Vector<T>::front() const
{
    return array[0];
}

template <typename T>
void Vector<T>::clear()
{
    theSize =0;
    theCapacity =0;
}


template <typename T>
const T & Vector<T>::back() const
{
    return  array[theSize-1];
}

template <typename T>
T & Vector<T>::back()
{
    return  array[theSize-1];
}

template <typename T>
void Vector<T>::pop_back()
{
    --theSize;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return &array[0];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return & array[0];
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return &array[theSize];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator itr)
{
    auto temp = itr;
    while(itr!=end())
    {
          *itr=*(itr+1);
          ++itr;
    }
    --theSize;
    return temp;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator start,
                                              iterator last)
{
    auto itr = start;
    int index = last - start;
    while(last!=end())
    {
       *start = *last;
       ++start;
       ++last;
    }
    theSize=theSize-index;
    return itr;
}
template <typename T>
void Vector<T>::resize(int num, T val)
{
    if (num>theSize)
    {
        T* temp = new T[num];
        for (int i =0;i<theSize;++i)
           { temp[i]=std::move(array[i]);}
        for (int j=theSize;j!=num;++j)
           { temp[j]=val;}
    swap(array,temp);
    temp = nullptr;
    theSize = num;
    theCapacity = num;
    }
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator itr,
                                                const T& val)
{
    T* temp = new T[++theCapacity];
    int index=itr-begin();
    for(int i=0;i<index;++i)
        { temp[i]=std::move(array[i]);}
    temp[index]=val;
    int marker=end()-begin();
    for(int j=index;j!=marker+1;++j)
       { temp[j+1]=std::move(array[j]);}
    swap(temp,array);
    ++theSize;
    delete []temp;
    return & array[index];
}



