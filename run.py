import subprocess
import time
import sys
import os

if len(sys.argv) < 2:
    print("ERROR: NOT ENOUGH ARGUMENTS")
    exit()

path = sys.argv[1]
binary_path = 'a.out'
if not os.path.isfile(path):
    print("ERROR: INPUT IS NOT A FILE")
    exit()

result = subprocess.run('g++ ' + path + ' -std=c++17 -o ' + binary_path, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
if(len(result.stderr) > 0):
    print("ERROR COMPILING:")
    print(result.stderr)
    exit()

# Record the start time
start_time = time.time()

# Run the bash command using subprocess
result = subprocess.run('./' + binary_path + ' < in.in > out.out', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

# Record the end time
end_time = time.time()

# Calculate the execution time
execution_time = end_time - start_time

# Print the error messages, if any
print("Errors:", result.stderr)

# Print the execution time
print("Execution time: {:.6f} seconds".format(execution_time))




