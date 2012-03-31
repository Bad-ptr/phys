#!/usr/bin/python2

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


kmp_module = Extension('_kmp',
                       sources=['../src/math/kmvector.c', '../src/math/kmquat.c', '../src/math/kmath.c', '../src/math/kmmatrix.c', '../src/shared/kbtypes.c', '../src/shared/shared.c', 'kmp.c', 'kmp_wrap.c'],
                       )

setup (name = 'kmp',
       version = '0.1',
       author      = "Constantin",
       description = """Constantin's math lib""",
       ext_modules = [kmp_module],
       py_modules = ['kmp'],
       )
