#!/usr/bin/env python3

import unittest
import math

from CosAB import cos_ab

class TestCosFunction(unittest.TestCase):

    def test_zero_addition(self):
    	result = cos_ab(0, 0)
    	self.assertAlmostEqual(result, 1.0)
    	
    def test_pi_addition(self):
    	result = cos_ab(math.pi/2, math.pi)
    	self.assertAlmostEqual(result, 0.0)
    	
    def test_negative_angle(self):
    	result = cos_ab(0, -math.pi)
    	self.assertAlmostEqual(result, -1.0)		
    	
if __name__ == '__main__':
   unittest.main()    	
