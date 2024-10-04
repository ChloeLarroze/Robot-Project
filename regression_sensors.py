# Import necessary libraries
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Intensity values for left infrared sensor (reversed order for calculation purposes)
Imax_left = [205, 250, 295, 291, 330, 350, 395, 458, 575, 695, 878, 2040, 3795]
Imax_left_sorted = sorted(Imax_left, reverse=True)

Imin_left = [167, 235, 275, 281, 315, 335, 385, 445, 565, 678, 860, 2010, 3785]
Imin_left_sorted = sorted(Imin_left, reverse=True)

# Distance values (sorted in increasing order)
distance_ = [np.inf, 30, 25, 22, 20, 18, 15, 12, 10, 8, 6, 4, 0]
distance = sorted(distance_)

# Calculate average intensity (Imoy) for left sensor
Imoy_left = [(Imax_left_sorted[i] + Imin_left_sorted[i]) / 2 for i in range(len(Imax_left_sorted))] 

# Convert infinite distance to a large value for plotting
distance[-1] = 50  # Setting infinity as a large value for better graph representation

# Calculate errors for left sensor (positive and negative error values)
errors_left = [(Imax_left_sorted[i] - Imoy_left[i], Imoy_left[i] - Imin_left_sorted[i]) for i in range(len(Imax_left_sorted))]
errors_left = np.array(errors_left).T  # Transpose to separate positive and negative errors

# Data for right infrared sensor (also reversed for calculation purposes)
Imax_right = [295, 345, 360, 395, 418, 465, 530, 690, 805, 1190, 1600, 2430, 3810]
Imax_right_sorted = sorted(Imax_right, reverse=True)

Imin_right = [280, 335, 348, 380, 405, 450, 521, 670, 790, 1160, 1590, 2420, 3795]
Imin_right_sorted = sorted(Imin_right, reverse=True)

# Calculate average intensity (Imoy) for right sensor
Imoy_right = [(Imax_right_sorted[i] + Imin_right_sorted[i]) / 2 for i in range(len(Imax_right_sorted))]
print(Imoy_right)

# Calculate errors for right sensor (positive and negative)
errors_right = [(Imax_right_sorted[i] - Imoy_right[i], Imoy_right[i] - Imin_right_sorted[i]) for i in range(len(Imax_right_sorted))]
errors_right = np.array(errors_right).T  # Transpose to separate positive and negative errors

# Plotting ----------------------------------------------------------------
plt.figure(figsize=(10, 6))

# Plot left infrared sensor data with error bars
plt.errorbar(distance, Imoy_left, yerr=errors_left, fmt='+', ecolor='b', capsize=5)  # Error bars
plt.scatter(distance, Imoy_left, color='b', label='Left Infrared Light Intensity', marker='+')

# Plot right infrared sensor data with error bars
plt.errorbar(distance, Imoy_right, yerr=errors_right, fmt='+', ecolor='r', capsize=5)  # Error bars
plt.scatter(distance, Imoy_right, color='r', label='Right Infrared Light Intensity', marker='+')


# Plot labels, title, and grid
plt.xlabel('Distance (cm)')
plt.ylabel('Average Light Intensity (Imoy)')
plt.title('Light Intensity with Error Bars and Regression')
plt.legend()
plt.grid(True)
plt.show()

# Uncomment below code for exponential regression if needed
# Left sensor regression (exponential decay)
# log_Imoy_left = np.log(Imoy_left)
# coeffs_left = np.polyfit(distance, log_Imoy_left, 1)
# a_left, b_left = coeffs_left
# A_left = np.exp(b_left)
# exp_func_left = lambda x: A_left * np.exp(a_left * x)
# print(f'Left IR regression function: f(d) = {A_left:.2f} * e^({a_left:.4f} * d)')
# x_vals = np.linspace(distance[0], distance[-1], 100)
# y_vals_left = exp_func_left(x_vals)

# Right sensor regression (exponential decay)
# log_Imoy_right = np.log(Imoy_right)
# coeffs_right = np.polyfit(distance, log_Imoy_right, 1)
# a_right, b_right = coeffs_right
# A_right = np.exp(b_right)
# exp_func_right = lambda x: A_right * np.exp(a_right * x)
# print(f'Right IR regression function: f(d) = {A_right:.2f} * e^({a_right:.4f} * d)')
# y_vals_right = exp_func_right(x_vals)

# # Plot regression lines
# plt.plot(x_vals, y_vals_left, color='dodgerblue', label='Left IR Regression')
# plt.plot(x_vals, y_vals_right, color='tomato', label='Right IR Regression')
