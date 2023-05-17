import numpy as np
import matplotlib.pyplot as plt



def relu(x):
    return np.maximum(0, x)


def relu_derivative(x):
    return np.where(x > 0, 1, 0)


def sign(x):
    if x > 0:
        return 1
    else:
        return 0


# Define the input data (pairs of numbers from -1 to 1)
X = []
y = []

for a, b in [(1, 1), (-1, 1), (1, -1), (-1, -1)]:
    X.append([a, b])
    y.append([sign(a) ^ sign(b)])

X = np.array(X)
y = np.array(y)

# Define the number of nodes in the hidden layer
num_hidden_nodes = 4

# Define the number of input and output nodes
num_input_nodes = X.shape[1]
num_output_nodes = y.shape[1]

# Initialize the weights for the hidden and output layers
weights_hidden = np.random.uniform(size=(num_input_nodes, num_hidden_nodes))
weights_output = np.random.uniform(size=(num_hidden_nodes, num_output_nodes))

# Define the learning rate and number of iterations
learning_rate = 0.05
num_iterations = 100_000

# Train the neural network
for i in range(num_iterations):
    # Forward pass
    hidden_layer_input = np.dot(X, weights_hidden)
    hidden_layer_output = relu(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, weights_output)
    output = relu(output_layer_input)

    # Backward pass
    error = y - output
    d_output = error * relu_derivative(output)
    error_hidden = d_output.dot(weights_output.T)
    d_hidden = error_hidden * relu_derivative(hidden_layer_output)

    # Update weights
    weights_output += hidden_layer_output.T.dot(d_output) * learning_rate
    weights_hidden += X.T.dot(d_hidden) * learning_rate

# Test the neural network
X_test = np.array([[0.8, 0.2], [-0.9, 0.4], [0.3, -0.6], [-0.2, -0.4], [1, 1], [-1, -1], [-1, 1], [1, -1]])
y_test = np.array([[1], [0], [0], [1], [1], [1], [0], [0]])


def predict(x):
    hidden_layer_input = np.dot(x, weights_hidden)
    hidden_layer_output = relu(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, weights_output)
    output = relu(output_layer_input)
    return output


# plot using heatmap

x = np.linspace(-1, 1, 100)
y = np.linspace(-1, 1, 100)
X, Y = np.meshgrid(x, y)
Z = predict(np.array([X.ravel(), Y.ravel()]).T).reshape(X.shape)

plt.pcolormesh(X, Y, Z, alpha=0.5)
plt.colorbar()
plt.title("XOR ReLU no Normalization")
plt.show()

print("Predictions on test data:")
for a, b in [(-1, -1), (-1, 1), (1, -1), (1, 1)]:
    print(f"({a}, {b}) -> {predict(np.array([[a, b]]))}")

if __name__ == "__main__":
    pass

