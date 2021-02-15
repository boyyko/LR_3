//
// Created by ubuntu on 08.02.2021.
//

#ifndef SHARED_PTR_SHARED_PTR_HPP
#define SHARED_PTR_SHARED_PTR_HPP

#include <atomic>
#include <iostream>
#include <algorithm>
#include <utility>

template <typename T>

class shared_ptr {
public:

    shared_ptr()
    {
        ptr = nullptr;
        count = nullptr;
    }

    explicit shared_ptr(T* point)
    {
        ptr = point;
        if (point == nullptr)
        {
            count = nullptr;
        }
        else
        {
            count = new std::atomic_uint;
            *count = 1;
        }
    }

    shared_ptr(const shared_ptr& obj)
    {
        ptr = obj.ptr;
        count = obj.count;
        if (ptr)
        {
            *count+=1;
        }
        else
        {
            count = nullptr;
        }
    }

    shared_ptr(shared_ptr&& obj)
    {
        ptr = obj.ptr;
        count = obj.count;
        obj.ptr = nullptr;
        obj.count = nullptr;
    }

    ~shared_ptr()
    {
        if (count)
        {
            if (*count == 1)
            {
                delete ptr;
                delete count;
            }
            else
            {
                *count-=1;
            }
        }
        ptr = nullptr;
        count = nullptr;
    }

    auto operator=(const shared_ptr& obj) -> shared_ptr&
    {
        if (this != &obj)
        {
            ptr = obj.ptr;
            count = obj.count;
            if (ptr)
            {
                *count+=1;
            }
            else
            {
                count = nullptr;
            }
        }
        return *this;
    }

    auto operator=(shared_ptr&& obj) -> shared_ptr&
    {
        if (this != &obj)
        {
            ptr = obj.ptr;
            count = obj.count;
        }
        return *this;
    }

    operator bool() const
    {
        if (ptr)
            return true;
        else
            return false;
    }

    auto operator*() const -> T&
    {
        if (ptr)
            return *ptr;
        else
            return nullptr;
    }

    auto operator->() const -> T*
    {
        return ptr;
    }

    auto get() -> T*
    {
        return ptr;
    }

    void reset()
    {
        if (*count == 1)
        {
            delete ptr;
            delete count;
        }
        else
        {
            *count-=1;
        }

        ptr = nullptr;
        count = nullptr;
    }

    void reset(T* point)
    {
        if (*count == 1)
        {
            delete ptr;
            delete count;
        }
        else
        {
            *count-=1;
        }
        ptr = point;
        if (point == nullptr)
        {
            count = nullptr;
        }
        else
        {
            count = new std::atomic_uint;
            *count = 1;
        }
    }

    void swap(shared_ptr& obj)
    {
        T* tmp_ptr(std::move(obj.ptr));
        obj.ptr = std::move(ptr);
        ptr = std::move(tmp_ptr);
        std::atomic_uint* tmp_count_ptr = obj.count;
        obj.count = count;
        count = tmp_count_ptr;
    }

    auto use_count() const -> size_t
    {
        if (count)
        {
            return *count;
        }
        else
        {
            return 0;
        }
    }

private:
    T* ptr;
    std::atomic_uint* count; // кол-во указателей на объект
};


#endif //SHARED_PTR_SHARED_PTR_HPP
