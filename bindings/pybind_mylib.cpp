#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "mylib.h"


namespace py = pybind11;


void py_init_module_mylib(py::module& m)
{
    m.def("create_context",
          CreateContext,
          pybind11::return_value_policy::reference);

    auto pyClassContext =
        py::class_<Context>
            (m, "Context", "")
        .def(py::init<>())
    ;
}
