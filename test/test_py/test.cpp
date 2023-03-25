#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

int main() {
    // Initialize Python interpreter
    py::scoped_interpreter guard{};

    try {
        // Load Python module
        py::module_ myModule = py::module_::import("myModule");
        py::object foo = myModule.attr("foo");

        // Call Python function with arguments
        int arg1 = 42;
        py::object result = foo(arg1);

        // Convert Python object to C++ type
        int result_value = result.cast<int>();

        std::cout << "Result: " << result_value << std::endl;

    } catch (const py::error_already_set& e) {
        // Handle Python exceptions
        std::cerr << "Python error:\n" << e.what() << std::endl;
    }

    return 0;
}