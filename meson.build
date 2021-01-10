project('experimental_qcs', 'c')
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)

lib_files = ['qop.c', 'qstate.c', 'sampling.c', 'unitaries.c']

experimental_qcs = [
    static_library('experimental_qcs', lib_files, dependencies: [m_dep])
]

executable('speed_test', 'speed_test.c',  dependencies: [m_dep], link_with: [experimental_qcs])

