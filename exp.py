#!/usr/bin/env python3

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from typing import List, Set, Optional

def expand(code, included):
    includes = [[m.start(), m.end(), code[m.start() : m.end()].replace("\n", "").replace(" ", "").replace(">", "").replace("#include<", "")] for m in re.finditer(
        r'#include\s*["<](cplib/[a-z_/]*(|.h))[">]\s*', code)]
    if(len(includes) == 0): 
        return code
    off = 0
    for s, e, include in includes:

        
        if(include in included):
            code = code[:s + off] + code[e + off:]
            off += s - e
        else:
            included.append(include)
            # get include
            ncode = ""
            with open(environ['CPLUS_INCLUDE_PATH'] + "/" + include, 'r') as file:
                ncode = file.read()
            ncode = ncode[ncode.find("// start\n") + 9:]
            code = code[:s + off] + ncode + code[e + off:]
            off += s - e + len(ncode)
    return expand(code, included)


if __name__ == "__main__":
    if(len(sys.argv) < 2):
        print("You need to specify the program to expand")
    else:
        code_path = sys.argv[1]
        code = ""
        with open(code_path, 'r') as file:
            code = file.read()
        code = expand(code, [])
        code = code.replace("// freopen", "freopen").replace("//freopen", "freopen")
        with open("submit.cpp", 'w') as file:
            file.write(code)