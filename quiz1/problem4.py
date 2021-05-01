from mrjob.job import MRJob

# Assumes there is only one high per date per airport in the data

class MRCompareHighs(MRJob):
    def mapper(self, _, line):
        info = line.split(",")
        airport = info[0]
        date = info[1]
        high = info[2]
        if date.strip() == "04/30/2021" and high:
            yield airport, float(high)  # differentiate by class
        elif date.strip() == "04/29/2021" and high:
            yield airport, high  # differentiate by class
    
    def combiner(self, airport, highs):
        thirty = None
        twenty_nine = None
        s = set(highs)  # at most containing two values, each of different class
        for temp in s:
            if isinstance(temp, float):  # high for 30th
                thirty = temp
            else:
                twenty_nine = float(temp)  # high for 29th
        if thirty and twenty_nine:
            if thirty > twenty_nine:
                yield airport, "True"
            # Else, yield nothing. Since we are assuming only one 
            # observation per date per airport, yielding nothing would
            # filter the passage of all info pertaining to that airport to
            # the reducer. 
        else:  # s containing only one value
            yield airport, s.pop()  
        
    
    def reducer(self, airport, highs):
        thirty = None
        twenty_nine = None
        for temp in highs: 
            if temp == "True": 
                yield airport, None
                break 
            elif isinstance(temp, float):  # high for 30th
                thirty = temp
            else:
                twenty_nine = float(temp)  # high for 29th
        if thirty and twenty_nine and thirty > twenty_nine:
            yield airport, None


if __name__ == '__main__': MRCompareHighs.run()

