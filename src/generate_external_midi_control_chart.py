#!/usr/bin/env python3

import os
import re

# script for generating an external MIDI control chart using constants defined in src/ConstantValues.h

abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

head_param="Parameter"
head_cc="CC"
max_param_length=len(head_param)
max_cc_length=len(head_cc)
mappings=[]
with open("ConstantValues.h", "r") as f:
    for line in f:
        line = line.strip()
        match = re.match("const uint8_t PARAM_MC_([^{]+)\\{([^}]+)\\}", line)
        if match:
            param = match.group(1)
            cc = match.group(2)
            if len(param) > max_param_length:
                max_param_length = len(param)
            if len(cc) > max_cc_length:
                max_cc_length = len(cc)

            mappings.append({
                'param': param,
                'cc': cc
            })

print(f"| {head_param.ljust(max_param_length)} | {head_cc.rjust(max_cc_length)} |")
print(f"| :{'-' * (max_param_length - 1)} | {'-' * (max_cc_length - 1)}: |")
for mapping in mappings:
    print(f"| {mapping['param'].ljust(max_param_length)} | {mapping['cc'].rjust(max_cc_length)} |")