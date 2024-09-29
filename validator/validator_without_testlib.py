import sys
inp = sys.stdin.read()
assert len(inp) == 4, 'Input must be 4 characters long'
assert inp[1] == ' ', 'Input must contain a space'
assert inp[0] in '123456789', 'First character must be a digit'
assert inp[2] in '123456789', 'Third character must be a digit'
assert inp[3] == '\n', 'Input must end with a newline'