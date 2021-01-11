project('experimental_qcs', 'c')
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)

lib_files = ['src/lib/qop.c', 'src/lib/qstate.c', 'src/lib/sampling.c', 'src/lib/unitaries.c']
include_dir = include_directories('src/lib')

experimental_qcs = [
    static_library('experimental_qcs', lib_files, dependencies: [m_dep])
]

executable('speed_test', 'src/speed_test.c',  dependencies: [m_dep], link_with: [experimental_qcs], include_directories: include_dir)

