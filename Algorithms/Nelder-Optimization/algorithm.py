import numpy as np


def target_function(point):
    x, y, z = point
    return -4 * x * (y ** 2) * z + 2 * (x ** 2) * y * (z ** 2) - 3 * x * y * z + 7 * (x ** 2) * (y ** 2)


def nelder_optimizer(f, initial, alpha=1., gamma=2., beta=0.5, sigma=0.5, t=1., iterations=100):
    v1 = initial
    v2 = initial + np.array((0, 0, t))
    v3 = initial + np.array((0, t, 0))

    target_optimal = initial

    for i in range(iterations):
        weighted_points = [(v1, f(v1)), (v2, f(v2)), (v3, f(v3))]
        points = sorted(weighted_points, key=lambda x: x[1])

        target_optimal = points[0][0]
        g = points[1][0]
        w = points[2][0]
        middle = (g + target_optimal) / 2
        xr = middle + alpha * (middle - w)

        if f(xr) < f(g):
            w = xr
        else:
            if f(xr) < f(w):
                w = xr
            c = (w + middle) / 2
            if f(c) < f(w):
                w = c

        if f(xr) < f(target_optimal):
            xe = middle + gamma * (xr - middle)
            if f(xe) < f(xr):
                w = xe
            else:
                w = xr

        if f(xr) > f(g):
            xc = middle + beta * (w - middle)

            if f(xc) < f(w):
                w = xc

        v1 = w
        v2 = v1 + sigma * (g - v1)
        v3 = v1 + sigma * (target_optimal - v1)

    return target_optimal, f(target_optimal)


def task():
    distance = 1.
    alpha = 1.
    gamma = 2.5
    beta = 0.5
    sigma = 0.5

    point, function_value = nelder_optimizer(
        f=target_function,
        initial=np.array((1., 3., 2.)),
        alpha=alpha,
        gamma=gamma,
        beta=beta,
        sigma=sigma,
        t=distance,
    )

    print(f"Optimal point: ({round(point[0])}, {round(point[1], 2)}, {round(point[2], 2)})")
    print(f"Optimal function value: F({round(point[0])}, {round(point[1], 2)}, {round(point[2], 2)}) = {round(function_value, 2)}")


if __name__ == "__main__":
    task()
