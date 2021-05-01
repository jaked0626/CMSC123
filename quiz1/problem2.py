from mrjob.job import MRJob

class MRFindAverage(MRJob):
    def mapper(self, _, line):
        info = line.split(",")
        airport = info[0]
        date = info[1].split("/")
        high = info[2]
        if date[0].strip() == "04":
            yield airport, high
    
    #def combiner(self, airport, highs):

    
    def reducer(self, airport, highs):
        obs = 0
        total = 0
        for temp in highs:  
            obs += 1
            total += int(temp)
        yield airport, total / obs
        
        
        


if __name__ == '__main__': MRFindAverage.run()