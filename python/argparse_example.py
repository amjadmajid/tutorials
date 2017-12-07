import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
# argument `integers` without - means it is required
parser.add_argument('integers', metavar='N', type=int, nargs='+',
                    help='an integer for the accumulator')
# argument `--sum` with -- it is a long argument form and it is optional 
parser.add_argument('--sum', dest='accumulate', action='store_const',
                    const=sum, default=max,
                    help='sum the integers (default: find the max)')

args = parser.parse_args()
print(args.accumulate(args.integers))