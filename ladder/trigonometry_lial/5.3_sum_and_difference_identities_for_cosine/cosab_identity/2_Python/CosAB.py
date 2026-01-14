#!/usr/bin/env python3

import math

def cos_ab(a,b):
   return math.cos(a) * math.cos(b) - math.sin(a) * math.sin(b)

print(f"cos(0 + 0) = {cos_ab(0, 0)}")
print(f"cos(math.pi/2 + math.pi) = {cos_ab(math.pi/2, math.pi)}")
