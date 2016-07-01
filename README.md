# Recover
A program to recover JPEGs from a forensic image (.raw) made out of deleted CompactFlash (CF) card.

Usage: ./recover infile; infile must be .raw format.

Reads data from infile, checks for JPEG signature and creates a new file with a filename ###.jpg for each JPEG found.
