import numpy as np

# Morse code to binary conversion (0 for dot, 1 for dash)
morse_code = {
    "A": ".-",    "B": "-...",  "C": "-.-.",  "D": "-..",   "E": ".", 
    "F": "..-.",  "G": "--.",   "H": "....",  "I": "..",    "J": ".---", 
    "K": "-.-",   "L": ".-..",  "M": "--",    "N": "-.",    "O": "---", 
    "P": ".--.",  "Q": "--.-",  "R": ".-.",   "S": "...",  "T": "-", 
    "U": "..-",   "V": "...-",  "W": ".--",   "X": "-..-",  "Y": "-.--", 
    "Z": "--.."
}

# Convert morse code to binary (0 for dot, 1 for dash)
def morse_to_input(morse):
    return [1 if char == '-' else 0 for char in morse]

# Prepare the input (morse) and output (letters) for training
inputs = [morse_to_input(morse) for morse in morse_code.values()]
outputs = [ord(letter) - ord('A') for letter in morse_code]  # Convert letter to index

# Print the dataset
print("Inputs (Morse code to binary):", inputs)
print("Outputs (Letters as numbers):", outputs)
