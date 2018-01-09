#pragma once

#include "conf.h"
#include "http.h"

namespace zia::api {
    /**
     * Interface for modules. Functions must be safe in a multithreading context.
     * Dynamic libraries of modules must export a "create" C function returning a "Module*" (caller should use smart pointers).
     */
    class Module {
    public:
        virtual ~Module() = default;

        /**
        * Called after contruct and when config changed.
        * \return true on success, otherwise false.
        */
        virtual bool config(const Conf& conf) = 0;

        /**
        * Called on HTTP request.
        * \return true on success, otherwise false.
        */
        virtual bool exec(HttpDuplex& http) = 0;

        /**
        * Called only for test (print an error message with the module's name)
        */
        virtual void test() const = 0;
    };
}
