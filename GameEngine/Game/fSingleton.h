#pragma once

//?e? class
template<typename T>
class fSingleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

protected:
    fSingleton() = default;
    ~fSingleton() = default;

    fSingleton(const fSingleton&) = delete;
    fSingleton& operator=(const fSingleton&) = delete;
    fSingleton(fSingleton&&) = delete;
    fSingleton& operator=(fSingleton&&) = delete;
};