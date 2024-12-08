import subprocess

# Command to execute

def get_res(n):
    command = [
        "python3", "x86.py", "-p", "test-and-set.s", "-M", "mutex,count", "-R", "ax,bx", "-a", "bx=100,bx=100", "-i", str(n), "-c"
    ]

    try:
        # Execute the command and capture the output
        result = subprocess.run(command, capture_output=True, text=True, check=True)

        # Get the output lines
        output_lines = result.stdout.strip().split('\n')

        # Extract the last line
        last_line = output_lines[-1] if output_lines else ""

        # Save the last line in a list
        output = last_line.split()[1]
        return int(output)

    except subprocess.CalledProcessError as e:
        print("Error occurred while executing the command:", e)
        print("Error message:", e.stderr)
        return -1


res = []
for i in range(1, 50):
    el = get_res(i)
    print(el)
    res.append((i, el))

print(res)