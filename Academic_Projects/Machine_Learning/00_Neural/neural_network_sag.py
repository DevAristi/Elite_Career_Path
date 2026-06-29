import math
import random


def weighted_sum(inputs, weights):
    limit = len(inputs)
    total_sum = 0
    for i in range(limit):
        total_sum += inputs[i] * weights[i]
    return total_sum


# Hyperbolic tangent activation function
def activation(x):
    if x > 20:
        return 1.0
    if x < -20:
        return -1.0
    res = (math.exp(x) - math.exp(-x)) / (math.exp(x) + math.exp(-x))
    return res


# Derivative of the hyperbolic tangent for Backpropagation
def activation_derivative(x):
    """f'(x) = 1 - f(x)^2"""
    act = activation(x)
    return 1.0 - (act * act)


class MultilayerNeuralNetwork:

    def __init__(self, n_inputs=4, n_hidden1=5, n_hidden2=4, n_outputs=3):
        self.n_inputs = n_inputs
        self.n_hidden1 = n_hidden1
        self.n_hidden2 = n_hidden2
        self.n_outputs = n_outputs

        # Hidden layer 1 weights and biases
        self.W1 = [
            [random.uniform(-1, 1) for _ in range(n_inputs)]
            for _ in range(n_hidden1)
        ]
        self.b1 = [random.uniform(-1, 1) for _ in range(n_hidden1)]

        # Hidden layer 2 weights and biases
        self.W2 = [
            [random.uniform(-1, 1) for _ in range(n_hidden1)]
            for _ in range(n_hidden2)
        ]
        self.b2 = [random.uniform(-1, 1) for _ in range(n_hidden2)]

        # Output layer weights and biases
        self.W3 = [
            [random.uniform(-1, 1) for _ in range(n_hidden2)]
            for _ in range(n_outputs)
        ]
        self.b3 = [random.uniform(-1, 1) for _ in range(n_outputs)]

    def feedforward(self, X):
        """Forward propagation of data."""
        self.A0 = X  # Input layer

        # --- Hidden Layer 1 ---
        self.Z1 = []
        self.A1 = []
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

    def backpropagation(self, Y, learning_rate):
        """Backward propagation algorithm to adjust weights and biases via Gradient Descent."""
        
        # 1. Calculate error and deltas (gradients) in Output Layer
        delta3 = []
        for i in range(self.n_outputs):
            error = Y[i] - self.A3[i]
            delta3.append(error * activation_derivative(self.Z3[i]))

        # 2. Calculate deltas (gradients) in Hidden Layer 2
        delta2 = []
        for j in range(self.n_hidden2):
            error_propagated = 0.0
            for k in range(self.n_outputs):
                error_propagated += self.W3[k][j] * delta3[k]
            delta2.append(error_propagated * activation_derivative(self.Z2[j]))

        # 3. Calculate deltas (gradients) in Hidden Layer 1
        delta1 = []
        for j in range(self.n_hidden1):
            error_propagated = 0.0
            for k in range(self.n_hidden2):
                error_propagated += self.W2[k][j] * delta2[k]
            delta1.append(error_propagated * activation_derivative(self.Z1[j]))

        # 4. Weights and Biases Optimization (Gradient Descent)
        # Update W3 and b3
        for i in range(self.n_outputs):
            self.b3[i] += learning_rate * delta3[i]
            for j in range(self.n_hidden2):
                self.W3[i][j] += learning_rate * delta3[i] * self.A2[j]

        # Update W2 and b2
        for i in range(self.n_hidden2):
            self.b2[i] += learning_rate * delta2[i]
            for j in range(self.n_hidden1):
                self.W2[i][j] += learning_rate * delta2[i] * self.A1[j]

        # Update W1 and b1
        for i in range(self.n_hidden1):
            self.b1[i] += learning_rate * delta1[i]
            for j in range(self.n_inputs):
                self.W1[i][j] += learning_rate * delta1[i] * self.A0[j]

    def train(self, X_train, Y_train, epochs=1000, learning_rate=0.1):
        """Full training loop execution."""
        for epoch in range(epochs):
            error_total = 0.0
            for x, y in zip(X_train, Y_train):
                # Forward pass
                prediction = self.feedforward(x)
                
                # Mean Squared Error calculation (for visualization metrics)
                for i in range(len(y)):
                    error_total += 0.5 * ((y[i] - prediction[i]) ** 2)
                
                # Backward pass
                self.backpropagation(y, learning_rate)

            # Performance reporting every 200 epochs
            if (epoch + 1) % 200 == 0:
                average_error = error_total / len(X_train)
                print(f"Epoch {epoch + 1}/{epochs} | Average Total Error: {average_error:.5f}")


# --- Execution and Training Datasets ---
if __name__ == "__main__":
    # Training Data (4 features per input -> 3 class labels per output)
    X_training = [
        [0.75, 0.12, 0.025, 0.47],
        [0.10, 0.90, 0.85, 0.05],
        [0.93, 0.75, 0.10, 0.88],
    ]

    Y_training = [
        [0.9, -0.9, -0.9],  # Class 1 target
        [-0.9, 0.9, -0.9],  # Class 2 target
        [-0.9, -0.9, 0.9],  # Class 3 target
    ]

    # Model instantiation
    mlp = MultilayerNeuralNetwork(4, 5, 4, 3)

    print("Initial testing before training:")
    for x in X_training:
        pred = mlp.feedforward(x)
        print(f"Input: {x} -> Raw Prediction: {[round(val, 3) for val in pred]}")

    print("\nStarting Network Training Run:")
    mlp.train(X_training, Y_training, epochs=1000, learning_rate=0.1)

    print("\nFinal evaluation post-training optimization:")
    for x in X_training:
        pred = mlp.feedforward(x)
        print(f"Input: {x} -> Optimized Output: {[round(val, 3) for val in pred]}")

    # --- Section 3: Final Inference Test Block ---
    print("\n" + "="*40)
    print("         INFERENCE EXECUTION")
    print("" + "="*40)
    
    # Run forward pass as pure inference without altering model parameters
    for i, x in enumerate(X_training):
        raw_prediction = mlp.feedforward(x)
        
        # Format the floating numbers for neat console output
        formatted_pred = [round(val, 3) for val in raw_prediction]
        
        print(f"\nTest Sample {i + 1}:")
        print(f"  Inputs            : {x}")
        print(f"  Network Output(tanh): {formatted_pred}")