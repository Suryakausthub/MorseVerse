import tensorflow as tf
import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# Morse code data as input
inputs = [
    [0, 0], [0, 1], [1, 0], [1, 1], [0, 0], [1, 0], [0, 1], [1, 0], [1, 0], [0, 1]
]  # Dummy data for demonstration

# Labels (one-hot encoding for letters A, B, C, etc.)
outputs = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]  # Example target labels for 10 letters

# Build a simple neural network model
model = Sequential([
    Dense(16, input_dim=4, activation='relu'),  # 4 because the max Morse code length is 4 (for B)
    Dense(26, activation='softmax')  # 26 output nodes for 26 letters
])

# Compile the model
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# Train the model
model.fit(inputs, outputs, epochs=100)

# Save the trained model
model.save('morse_code_model.h5')

print("Model training completed and saved!")
