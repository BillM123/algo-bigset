# Open the file
with open(input("Enter input: "), 'r') as file:
    # Read the lines
    lines = file.readlines()

# Open the output file
with open(input("Enter output: "), 'w') as file:
    # Iterate over the lines
    for line in lines:

        # If the line contains "The CPL is:"
        if "Bigger graph size:" in line:
            # Remove "The CPL is: " from the line
            line = line.replace("Bigger graph size: ", "")
            # Write it to the output file
            file.write(line)