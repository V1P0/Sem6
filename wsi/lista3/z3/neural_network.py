import numpy as np

class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size, activation_function):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size
        self.activation_function = activation_function

        self.W1 = np.random.randn(self.input_size, self.hidden_size)
        self.W2 = np.random.randn(self.hidden_size, self.output_size)
        self.B1 = np.zeros((1, self.hidden_size))
        self.B2 = np.zeros((1, self.output_size))


    def forward(self, X):
        self.z2 = np.dot(X, self.W1) + self.B1
        self.a2 = self.activation_function(self.z2)
        self.z3 = np.dot(self.a2, self.W2) + self.B2
        o = self.activation_function(self.z3)
        return o

    def backward(self, X, y, o, learning_rate=0.05):
        self.o_error = y - o
        self.o_delta = self.o_error * self.activation_function(o, deriv=True)

        self.z2_error = self.o_delta.dot(self.W2.T)
        self.z2_delta = self.z2_error * self.activation_function(self.a2, deriv=True)

        self.W1 += X.T.dot(self.z2_delta) * learning_rate
        self.W2 += self.a2.T.dot(self.o_delta) * learning_rate
        self.B1 += np.sum(self.z2_delta, axis=0, keepdims=True) * learning_rate
        self.B2 += np.sum(self.o_delta, axis=0, keepdims=True) * learning_rate

    def train(self, X, y, epochs, learning_rate=0.05):
        for epoch in range(epochs):
            o = self.forward(X)
            self.backward(X, y, o, learning_rate=learning_rate)
            if epoch % 10000 == 0:
                print(f"Error: {np.mean(np.abs(self.o_error))}")