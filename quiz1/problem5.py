from mrjob.job import MRJob
import math

# Assuming one entry per date per airport in csv file 

class MRHistogram(MRJob):
    def mapper(self, _, line):
        info = line.split(",")
        date = info[1]
        high = info[2]
        if date.strip() == "04/30/2021" and high:
            high = float(high)
            lb = math.floor(high / 10) * 10
            ub = lb + 10
            yield "{}-{}".format(lb, ub), 1 
    
    def combiner(self, range_, counts):
        yield range_, sum(counts)
    
    def reducer(self, range_, counts):
        yield range_, sum(counts)


if __name__ == '__main__': MRHistogram.run()

