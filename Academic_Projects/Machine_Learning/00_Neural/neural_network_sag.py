import math
import random


def weighted_sum(inputs, weights):
    limit = len(inputs)
    total_sum = 0
    for i in range(limit):
        total_sum += inputs[i] * weights[i]
    return total_sum


# Hyperbolic tangent
def activation(x):
    if x > 20:
        return 1.0
    if x < -20:
        return -1.0
    res = (math.exp(x) - math.exp(-x)) / (math.exp(x) + math.exp(-x))
    return res


def neuron(weights, inputs, bias):
    value = weighted_sum(inputs, weights) + bias
    output = activation(value)
    return output


def activation_derivative(x):
    """Derivative of the hyperbolic tangent for Backpropagation.

    f'(x) = 1 - f(x)^2
    """
    act = activation(x)
    return 1 - (act * act)


class MultilayerNeuralNetwork:

    def __init__(
        self,
        n_inputs=4,
        n_hidden1=5,
        n_hidden2=4,
        n_outputs=3,
    ):
        self.n_inputs = n_inputs
        self.n_hidden1 = n_hidden1
        self.n_hidden2 = n_hidden2
        self.n_outputs = n_outputs

        # Hidden layer 1 weights
        self.W1 = [
            [random.uniform(-1, 1) for _ in range(n_inputs)]
            for _ in range(n_hidden1)
        ]
        # Hidden layer 1 biases
        self.b1 = [random.uniform(-1, 1) for _ in range(n_hidden1)]

        # Hidden layer 2 weights
        self.W2 = [
            [random.uniform(-1, 1) for _ in range(n_hidden1)]
            for _ in range(n_hidden2)
        ]
        # Hidden layer 2 biases
        self.b2 = [random.uniform(-1, 1) for _ in range(n_hidden2)]

        # Output layer weights
        self.W3 = [
            [random.uniform(-1, 1) for _ in range(n_hidden2)]
            for _ in range(n_outputs)
        ]
        # Output layer biases
        self.b3 = [random.uniform(-1, 1) for _ in range(n_outputs)]

    def feedforward(self, X):
        """Forward propagation of data."""
        self.A0 = X  # Input layer

        # --- Hidden Layer 1 ---
        self.Z1 = []  # Values before activation
        self.A1 = []  # Values after activation
        for i in range(self.n_hidden1):
            z = weighted_sum(self.A0, self.W1[i]) + self.b1[i]
            self.Z1.append(z)
            self.A1.append(activation(z))

        # --- Hidden Layer 2 ---
        self.Z2 = []
        self.A2 = []
        for i in range(self.n_hidden2):
            z = weighted_sum(self.A1, self.W2[i]) + self.b2[i]
            self.Z2.append(z)
            self.A2.append(activation(z))

        # --- Output Layer ---
        self.Z3 = []
        self.A3 = []
        for i in range(self.n_outputs):
            z = weighted_sum(self.A2, self.W3[i]) + self.b3[i]
            self.Z3.append(z)
            self.A3.append(activation(z))

        return self.A3


X_input = [
    [0.75, 0.12, 0.025, 0.47],
    [0.10, 0.52, 0.809, 0.09],
    [0.94, 0.75, 0.35, 0.4],
]

# Instantiate the network (4 inputs, 5 hidden, 4 hidden, 3 outputs)
mlp = MultilayerNeuralNetwork(4, 5, 4, 3)

print("\nPrediction: ")
for i, x in enumerate(X_input):
    pred = mlp.feedforward(x)
    formatted_pred = [round(val, 3) for val in pred]
    print(f"Input: {x} -> Predicted Output: {formatted_pred}")

