from mrjob.job import MRJob

class MRairportsfound(MRJob):
    def mapper(self, _, line):
        airport = line.split(",")[0]
        if airport and airport != "airport":
            yield airport, None
    
    def combiner(self, airport, _):
        yield airport, None
    
    def reducer(self, airport, nonevalues):
        """ for x in nonevalues:  
            yield airport, None
            break  # breaks at first instance of the airport name """
        yield airport, None

if __name__ == '__main__': MRairportsfound.run()