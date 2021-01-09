import io
import subprocess
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation

NUM_DOF = 12


def get_heatmap(phis):
    with subprocess.Popen(["./builddir/main"], stdin=subprocess.PIPE, stdout=subprocess.PIPE) as process:
        out, errs = process.communicate(input=("\n".join((str(i) for i in phis)) + "\n").encode("UTF-8"))

    s = io.StringIO(out.decode("UTF-8"))
    s.seek(0,0)
    res = np.loadtxt(s, delimiter=",")
    return res


#get_heatmap([ 5.29683196,  5.38560137,  3.29346721, -5.52313328, -4.40234988,
#        1.95117847,  1.6NUM_DOF50749,  4.63700674,  5.15551132,  0.63872836,
#        1.05582973, -0.45NUM_DOF1964, -2.93235769,  0.30883892,  2.13654636])

d0 = [0] * NUM_DOF

fig = plt.figure()
ax = plt.axes(xlim=(0, 256), ylim=(0, 256))
im = plt.imshow(get_heatmap(d0), cmap="seismic", interpolation="none")

nsteps = 512

def init():
    im.set_data(get_heatmap(d0))
    return [im]

def animate(i):
    #a = np.array(d0)
    #a[0] = (i * 2*np.pi) / nsteps
    #a[1] = (i * 2*np.pi) / nsteps
    #print(a)
    a = [(i * 2*np.pi) / nsteps] * NUM_DOF
    print(f"{i * 100 / nsteps} %")
    im.set_array(get_heatmap(a))
    return [im]


ani = animation.FuncAnimation(fig, animate, init_func=init, frames=nsteps, interval=20, blit=True)
ani.save("animation.mp4", fps=30)
#plt.show()
