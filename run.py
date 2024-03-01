import subprocess
import time
import sys
import os

if len(sys.argv) < 2:
    print('ERROR: NOT ENOUGH ARGUMENTS')
    exit()

path = sys.argv[1]
binary_path = 'a.out'
if not os.path.isfile(path):
    print('ERROR: INPUT IS NOT A FILE')
    exit()


flags = ' -std=c++17 -O2 -g -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wduplicated-cond -Wlogical-op '

result = subprocess.run('g++ ' + path + ' ' + flags + ' -o ' + binary_path, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
if(": error:" in result.stderr):
    print('ERROR COMPILING:')
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
print('Errors:', result.stderr[:-1])

# Print the execution time
print('Execution time: {:.6f} seconds'.format(execution_time))

if len(result.stderr) > 0:
    print()
    result = subprocess.run('gdb ./' + binary_path + ' < debug.in', shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    cause = result.stdout[:result.stdout.rindex("gdb") - 2]
    cause = cause[cause.rindex("gdb") + 5:]
    print('Debugger:')
    print(cause)





