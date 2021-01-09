project('easy_qcs', 'c')
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)

lib_files = ['qop.c', 'qstate.c', 'sampling.c', 'unitaries.c']

easy_qcs = [
    static_library('easy_qcs', lib_files, dependencies: [m_dep])
]

executable('speed_test', 'speed_test.c',  dependencies: [m_dep], link_with: [easy_qcs])

