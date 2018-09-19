#Austin Zhang
#604736503
#CS35L Lab 3
#shuf.py

#The basis of this script was taken from randline.py, as provided in the assignment spec.

#!/usr/bin/python

"""
Output lines selected randomly from a file

Copyright 2005, 2007 Paul Eggert.
Copyright 2010 Darrell Benjamin Carbajal.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Please see <http://www.gnu.org/licenses/> for a copy of the license.

$Id: randline.py,v 1.4 2010/04/05 20:04:43 eggert Exp $
"""

import sys,random
import arg

class shuf:
	def __init__(self, filename):
		f = open (filename, 'r')
		self.lines = f.readlines()
		f.close ()

	def chooseline(self):
		return random.choice(self.lines)

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE

Output randomly shuffled lines from FILE."""
	
	#updated parser
    parser = argparse.ArgumentParser(description='shuffles input.')
    parser.add_argument("-n", "--numlines",
                      action="store", dest="numlines",
                      help="output")
    parser.add_argument("-e", "--echo", dest="echolines", default=None, nargs='+',
                      action="store", help="ARG as input line")
    parser.add_argument("-r", "--repeat", dest="repeat", default=False, const=True,
                      action="store_const", help="")
    args = parser.parse_args()

    in_line = args.echolines #input lines
    

    try:
        numlines = int(args.numlines)
    except:
        numlines = len(in_line) #length of input lines
    if numlines < 0:
        parser.error("negative count: {0}".
                     format(numlines)) #same as randline.py
    if args.repeat:
        for i in range(numlines):
            line=random.choice(in_line)
            print(line) 
    else:
        lines=random.sample(in_line, numlines)
        for line in lines:
            print(line) #print line in lines

if __name__ == "__main__":
    main()