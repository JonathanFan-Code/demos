import os
import subprocess
import time

processes = []
try:
    for i in range(1):
        processes.append(subprocess.Popen(["python.exe", "agora.py"]))
        time.sleep(5)

    a = input()
finally:
    for i in range(len(processes)):
        processes[i].kill()

