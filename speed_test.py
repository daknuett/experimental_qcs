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
        process = subprocess.run([meson, "configure", builddir, "-D", f"c_args=\"{' '.join(macros)}\""])
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


def get_runtime_data(macros, nruns=2):
    set_macros(macros)
    compile()
    N = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    print("#"*20)
    print("MACROS ARE:", macros)
    T = [get_execution_time(n, nruns) for n in N]
    return N, T

def get_runtime_data_dict(macros, nruns=2):
    N, T = get_runtime_data(macros, nruns)
    return {"macros": macros, "nruns": nruns, "N": N, "T": T}

macro_sets = [[]]
nruns = 3
output_name = "data.json"

setup()
results = [get_runtime_data_dict(ms, nruns) for ms in macro_sets]

with open(output_name, "w") as fout:
    json.dump(results, fout)
print("results written to", output_name)

