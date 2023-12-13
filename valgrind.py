import sys
import subprocess

# Check usage
if len(sys.argv) != 2:
    print("\nError. Usage: python valgrind.py program.exe\n")
    exit()

# Get filenames
python_file = sys.argv[0].split("/")[-1]
log_file = python_file.replace(".py", ".log")
c_exe = sys.argv[1]

# Execute valgrind command
proc = subprocess.Popen(["valgrind", "--log-file=%s" % log_file, "-v", "--leak-check=full", c_exe], stdout=subprocess.PIPE)
out, err = proc.communicate()
if err:
    print("Error running valgrind:", err)
    exit()

# Print last lines of log file to terminal (tail)
with open(log_file, "r") as fh:
    lines = fh.readlines()

for i in range(-15, -1):
    print(lines[i])