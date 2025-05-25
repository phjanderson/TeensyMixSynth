#ifndef fnptr_h
#define fnptr_h

// template to allow capturing on regular function pointers
// see [SynthController.h](SynthController.h) for actual usage of fnptr
// source: https://stackoverflow.com/a/45365798

// please note: this template uses static storage for captured variables, all instances of the same lambda will share the same captured variable values!

#include<type_traits>
#include<utility>
#include<new>

template<int, typename Callable, typename Ret, typename... Args>
auto fnptr_(Callable&& c, Ret (*)(Args...))
{
    static std::decay_t<Callable> storage = std::forward<Callable>(c);
    static bool used = false;
    if(used)
    {
        using type = decltype(storage);
        storage.~type();
        new (&storage) type(std::forward<Callable>(c));
    }
    used = true;

    return [](Args... args) -> Ret {
        auto& c = *std::launder(&storage);
        return Ret(c(std::forward<Args>(args)...));
    };
}

template<typename Fn, int N = 0, typename Callable>
Fn* fnptr(Callable&& c)
{
    return fnptr_<N>(std::forward<Callable>(c), (Fn*)nullptr);
}

#endif