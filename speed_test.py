import io
import os
import subprocess
import numpy as np
import json

builddir = "builddir"
meson = "meson"
speed_test = os.path.join(builddir, "speed_test")

def setup():
    if(os.path.exists(builddir)):
        return
    process = subprocess.run([meson, "setup", builddir])
    if(process.returncode != 0):
        raise OSError(process.stderr)

def set_macros(macros):
    if(macros):
        macros = ["-D" + macro for macro in macros]
        macro_string = ' '.join(macros)
        print("macro string:", macro_string)
        process = subprocess.run([meson, "configure", builddir, "-D", f"c_args={macro_string}"])
    else:
        process = subprocess.run([meson, "configure", builddir, "-D", f"c_args=\"-DMESON_DOES_NOT_LIKE_EMPTY_C_ARGS\""])
    if(process.returncode != 0):
        raise OSError(process.stderr)

def compile():
    process = subprocess.run([meson, "compile", "-C", builddir])
    if(process.returncode != 0):
        raise OSError(process.stderr)

def get_execution_time(n, nruns):
    def do(n):
        print("running with n =", n, "...")
        process = subprocess.Popen([speed_test, f"{n}".encode("UTF-8")], stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        stdout, stderr = process.communicate()
        if(process.returncode != 0):
            raise OSError(stderr)
        return int(stdout.decode("UTF-8").strip())

    return min((do(n) for _ in range(nruns)))


def get_runtime_data(macros, N, nruns=2):
    set_macros(macros)
    compile()
    print("#"*20)
    print("MACROS ARE:", macros)
    T = [get_execution_time(n, nruns) for n in N]
    return N, T

def get_runtime_data_dict(macros, N, nruns=2):
    N, T = get_runtime_data(macros, N, nruns)
    return {"macros": macros, "nruns": nruns, "N": N, "T": T}

N = [6, 7, 8, 9, 10, 11, 12]
macro_sets = [["SIMPLE_QSTATE"], ["CHUNKED_QSTATE", "CHUNK_SIZE=10"], ["CHUNKED_QSTATE", "CHUNK_SIZE=40"]]
nruns = 3
output_name = "data.json"

setup()
results = [get_runtime_data_dict(ms, N, nruns) for ms in macro_sets]

with open(output_name, "w") as fout:
    json.dump(results, fout)
print("results written to", output_name)

