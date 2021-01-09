import matplotlib.pyplot as plt
import json

with open("data.json") as fin:
    data = json.load(fin)

def mk_label(dset):
    return f"Options: {','.join(dset['macros'])}, best of {dset['nruns']}"

plt.yscale("log")

handles = [plt.plot(dset["N"], dset["T"], label=mk_label(dset))[0] for dset in data]
plt.legend(handles=handles)

plt.show()
