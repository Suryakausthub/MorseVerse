def convert_to_header(input_file, output_file, var_name):
    with open(input_file, 'rb') as f:
        data = f.read()

    with open(output_file, 'w') as f:
        f.write(f"#ifndef MODEL_DATA_H\n#define MODEL_DATA_H\n\n")
        f.write(f"const unsigned char {var_name}[] = {{\n")

        for i in range(0, len(data), 12):
            chunk = data[i:i+12]
            line = ', '.join(f'0x{b:02x}' for b in chunk)
            f.write(f"  {line},\n")

        f.write(f"}};\n\n")
        f.write(f"const int {var_name}_len = {len(data)};\n")
        f.write(f"#define g_model {var_name}\n#define g_model_len {var_name}_len\n\n")
        f.write(f"#endif  // MODEL_DATA_H\n")


# Run this
convert_to_header(
    input_file="model/morse_model.tflite",
    output_file="src/model_data.h",
    var_name="morse_model_data"
)
