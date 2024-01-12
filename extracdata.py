import argparse
import re

def extract_data(file_path, *fields):
    data = {field: [] for field in fields}  # Initialize a dictionary to hold the data
    with open(file_path, 'r') as file:
        for line in file:
            for field in fields:
                if field in line:
                    # Extract the numeric value after the colon and strip whitespace
                    value = re.search(r':\s*(\S+)', line).group(1)
                    data[field].append(value)

    return data

def print_data(data):
    # Find the longest field name for formatting
    field_width = max(len(field) for field in data.keys())
    # Print the field names as column headers
    for field in data:
        print(f"{field:<{field_width}}", end=' ')
    print()  # Newline after headers
    # Print the data in columns
    for i in range(len(next(iter(data.values())))):  # Use the length of the first data list
        for field in data:
            print(f"{data[field][i]:<{field_width}}", end=' ')
        print()

def main():
    parser = argparse.ArgumentParser(description="Extract data from a raw file.")
    parser.add_argument("file_path", help="The path to the raw file")
    parser.add_argument('fields', nargs='+', help="The fields to extract from the file")
    args = parser.parse_args()

    # Define the fields to extract
    fields_to_extract = args.fields

    # Extract the data
    data = extract_data(args.file_path, *fields_to_extract)

    # Print the data
    print_data(data)

if __name__ == "__main__":
    main()