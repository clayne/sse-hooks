#! /usr/bin/env python
# encoding: utf-8

import os

VERSION='1.0.0'
APPNAME='sse-hooks'

top = '.'
out = 'out'

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

    if conf.env['CXX_NAME'] is 'gcc':
        conf.check_cxx (msg="Checking for '-std=c++17'", cxxflags='-std=c++17') 
        conf.env.append_unique('CXXFLAGS', ['-std=c++17', "-O2", "-Wno-deprecated-declarations"])
        conf.env.append_unique('LDFLAGS', ['-lpthread'])
    elif conf.env['CXX_NAME'] is 'msvc':
        conf.env.append_unique('CXXFLAGS', ['/EHsc', '/MT', '/O2'])

def build(bld):
    bld.shlib (target=APPNAME, 
        source = bld.path.ant_glob ("src/*.cpp", excl=["**/test_*.cpp"]), 
        includes=['src', 'include'])
    for src in bld.path.ant_glob ("**/test_*.cpp"):
        f = os.path.basename (str (src))
        f = os.path.splitext (f)[0]
        bld.program (target=f, source=[src], includes='include', use=APPNAME)