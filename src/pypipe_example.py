import os
import tempfile
import subprocess
from subprocess import check_output

with tempfile.NamedTemporaryFile() as file:
    file.write("1\t2\n3\t4\n")
    file.delete = False

try:
    p = subprocess.Popen(["awk", '{print $1 - 2}', file.name],
              stdout=subprocess.PIPE)
    output = p.communicate()[0]
    print output
    # or
    # output = check_output(["pram_axdnull", str(kmer), input_filename, file.name])
finally:
    os.remove(file.name)
