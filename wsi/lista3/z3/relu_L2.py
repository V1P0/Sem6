from neural_network import NeuralNetwork
import numpy as np
import matplotlib.pyplot as plt

def L2(x, y):
    if(x == 0 and y == 0):
        return 0, 0
    d = np.sqrt(x**2 + y**2)
    return x/d, y/d

# Define the activation function
def activation_function(x, deriv=False):
    if deriv:
        return np.where(x >= 0, 1, 0)
    return np.where(x >= 0, x, 0)

def sign(x):
    if x > 0:
        return 1
    else:
        return 0

# Define the input data (pairs of numbers from -1 to 1)
X = []
y = []

for a in range(-20, 21):
    for b in range(-20, 21):
        X.append([*L2(a/20, b/20)])
        y.append([1 if sign(a)==sign(b/10) else 0])


X = np.array(X)
y = np.array(y)

# Define the Neural Network
nn = NeuralNetwork(input_size=2, hidden_size=4, output_size=1, activation_function=activation_function)

# Train the Neural Network
nn.train(X, y, epochs=100_000, learning_rate=0.05)

# Print the output
x = np.linspace(-1, 1, 100)    
y = np.linspace(-1, 1, 100)
normalized = np.array([[*L2(a, b)] for a, b in zip(x, y)])
x = [a[0] for a in normalized]
y = [a[1] for a in normalized]
X, Y = np.meshgrid(x, y)
Z = nn.forward(np.array([X.ravel(), Y.ravel()]).T).reshape(X.shape)

plt.pcolormesh(X, Y, Z, alpha=0.5)
plt.colorbar()
plt.title("ReLU L2")
plt.show()

print("Predictions on test data:")
for a, b in [(-1, -1), (-1, 1), (1, -1), (1, 1)]:
    print(f"({a}, {b}) -> {nn.forward(np.array([[a, b]]))}")



