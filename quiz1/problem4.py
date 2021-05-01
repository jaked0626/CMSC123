from mrjob.job import MRJob

# Assumes there is only one high per date per airport in the data

class MRCompareHighs(MRJob):
    def mapper(self, _, line):
        info = line.split(",")
        airport = info[0]
        date = info[1]
        high = info[2]
        if date.strip() == "04/30/2021":
            yield airport, ",".join(high, "30")  
        elif date.strip() == "04/29/2021" and high:
            yield airport, ",".join(high, "29")
    
    def combiner(self, airport, highs):
        thirty = None
        twenty_nine = None
        s = set(highs)  
        for temp in s:
            if temp.split[1] == "30"


if __name__ == '__main__': MRCompareHighs.run()

