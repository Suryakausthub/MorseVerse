import tensorflow as tf

# Load the trained model
model = tf.keras.models.load_model('morse_code_model.h5')

# Convert the model to TensorFlow Lite format
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Save the TFLite model
with open('morse_code_model.tflite', 'wb') as f:
    f.write(tflite_model)

print("TensorFlow Lite model saved as 'morse_code_model.tflite'")
