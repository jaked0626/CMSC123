from mrjob.job import MRJob

class MRUniqueCount(MRJob):
    def mapper(self, _, line):
        airport = line.split(",")[0]
        if airport and airport != "airport":
            yield airport, None
    
    def combiner(self, airport, _):
        yield airport, None
    
    def reducer_init(self):
        self.unique_count = 0
    
    def reducer(self, airport, _): 
        self.unique_count += 1

    def reducer_final(self):
        yield "Number of unique airports:", self.unique_count
    
        


if __name__ == '__main__': MRUniqueCount.run()

