#include <boost/test/unit_test.hpp>

#include <Python.h>

#include <boost/python/import.hpp>
#include <boost_python_exception/clear_exception.hpp>

namespace bp=boost::python;
namespace bpe=boost_python_exception;

BOOST_AUTO_TEST_SUITE( clear_exception )

BOOST_AUTO_TEST_CASE( no_extant_exception )
{
    PyErr_Clear();
    BOOST_CHECK(!PyErr_Occurred());

    bpe::clear_exception();

    BOOST_CHECK(!PyErr_Occurred());
}

BOOST_AUTO_TEST_CASE( extant_exception )
{
    try {
        bp::import("no_such_module_name_exists_I_hope");
        BOOST_CHECK(false);
    }
    catch (const bp::error_already_set&) {
        BOOST_CHECK(PyErr_Occurred());
        bpe::clear_exception();
        BOOST_CHECK(!PyErr_Occurred());
    }

}

BOOST_AUTO_TEST_SUITE_END()
