import io
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.widgets import Slider

NUM_DOF = 12

def get_heatmap(phis):
    with subprocess.Popen(["./main"], stdin=subprocess.PIPE, stdout=subprocess.PIPE) as process:
        out, errs = process.communicate(input=("\n".join((str(i) for i in phis)) + "\n").encode("UTF-8"))

    s = io.StringIO(out.decode("UTF-8"))
    s.seek(0,0)
    res = np.loadtxt(s, delimiter=",")
    return res

slidercolor = "lightgoldenrodyellow"
fig = plt.figure()
ax = plt.axes(xlim=(0, 256), ylim=(0, 256))
im = plt.imshow(get_heatmap([0]*NUM_DOF), cmap="seismic", interpolation="none")

slideraxes = [plt.axes([0.025, 0.1 + 0.05*i, 0.65, 0.03], facecolor=slidercolor) for i in range(NUM_DOF)]
sliders = [Slider(a, f"$\phi_{i}$", 0, 2*np.pi, valinit=0) for i,a in enumerate(slideraxes)]

def update(val):
    values = [s.val for s in sliders]
    im.set_array(get_heatmap(values))
    fig.canvas.draw_idle()

for s in sliders:
    s.on_changed(update)

plt.show()
