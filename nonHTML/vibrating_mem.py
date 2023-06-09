# Made by Daniel Naumov
# June 08 2023
import numpy as np
import matplotlib.pyplot as plt
from scipy.special import jn, jn_zeros
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

R, a, b, c, d = 2, .5, .5, 1, 1
k, l = 3, 4
r_s = np.linspace(0, R, 50)
theta_s = np.linspace(0, 2*np.pi, 50)
t_s = np.linspace(0, 2*np.pi, 96)
r, theta = np.meshgrid(r_s, theta_s)
X, Y = r * np.cos(theta), r * np.sin(theta)
fig = plt.figure(figsize=(l*4, (k+1)*4))  # Scale the figure size based on the number of tiles

# Define the function to update the plot at each time step
def update_plot(t):
    fig.clear()

    # Iterate over all vibrating membrane functions
    for n in np.arange(0, k+1):
        for m in np.arange(0, l):
            ax = fig.add_subplot(k+1, l, n*l+m+1, projection='3d')
            radial = (a * np.cos(n * theta) + b * np.sin(n * theta))
            p = jn_zeros(n, l)
            alpha = p[m]
            time = (c * np.cos(t) + d * np.sin(t))
            z = jn(n, alpha * r / R) * radial
            z *= time  # Update the z-coordinate
            ax.plot_surface(X, Y, z, cmap=plt.cm.twilight_r)
            ax.set_title(f'Mode {n}{m+1} at t={t:.1f}')
            ax.set_zlim(-.75, .75)
plt.tight_layout()
# Create and save the animation
anim = FuncAnimation(fig, update_plot, frames=t_s, interval=10)
anim.save('vibrating_membrane.gif', writer='ffmpeg', fps=48)

plt.show()
