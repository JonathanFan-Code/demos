import os
import subprocess
import time

processes = []
try:
    for i in range(6):
        processes.append(subprocess.Popen(["python.exe", "agora.py"]))
        time.sleep(5)

    a = input()
finally:
    for i in range(len(processes)):
        processes[i].kill()

