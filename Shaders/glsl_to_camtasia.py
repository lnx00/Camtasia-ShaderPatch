import json
import argparse
import os


def escape_string(s):
    """Escape the string to fit into a JSON field"""
    return (
        s.replace("\\", "\\\\")
        .replace('"', '\\"')
        .replace("\n", "\\n")
        .replace("\r", "\\r")
    )

def read_existing_json(filename):
    """Read and return JSON content from an existing file."""
    try:
        with open(filename, 'r') as file:
            return json.load(file)
    except IOError:
        return None
    except json.JSONDecodeError:
        return None

def main():
    parser = argparse.ArgumentParser(description="Process GLSL into the Camtasia Shader format.")
    parser.add_argument("filename", help="Path to the input GLSL file")
    parser.add_argument("-name", help="Name field for the Shader")
    args = parser.parse_args()

    # Retrieve the arguments
    glsl_file_path = args.filename
    output_file_path = os.path.splitext(glsl_file_path)[0] + ".tscshadervid"
    shader_name = args.name or os.path.splitext(os.path.basename(glsl_file_path))[0]

    # Read the GLSL input file
    try:
        with open(glsl_file_path, "r") as file:
            glsl_code = file.read()
    except IOError as e:
        print(f"Error reading file {glsl_file_path}: {e}")
        return

    # Encode/Update the JSON output
    output_json = read_existing_json(output_file_path)

    if output_json:
        output_json["code"] = glsl_code
        output_json["name"] = args.name or output_json["name"]
    else:
        output_json = {
            "code": glsl_code,
            "effectDef": [],
            "width": 1920,
            "height": 1080,
            "name": shader_name,
            "version": 1.0,
        }

    # Write the JSON output to a file
    try:
        with open(output_file_path, "w") as outfile:
            json.dump(output_json, outfile, indent=4)
        print(f"JSON output written to {output_file_path}")
    except IOError as e:
        print(f"Error writing file {output_file_path}: {e}")


if __name__ == "__main__":
    main()
