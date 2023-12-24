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

speedup_flag = False
for arg in sys.argv[2:]:
    if arg == '-speedup':
        speedup_flag = True

flags = '-Wall -Wextra -pedantic -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wno-sign-compare -Wno-unused-result -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover -fstack-protector -fanalyzer'

if speedup_flag:
    flags = '-std=c++17 -O2'

result = subprocess.run('g++ ' + path + ' ' + flags + ' -o ' + binary_path, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
if(len(result.stderr) > 0):
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
print('Errors:', result.stderr)

# Print the execution time
print('Execution time: {:.6f} seconds'.format(execution_time))




