from mrjob.job import MRJob
import re

with open("data.csv", "r") as f:
    first_line = f.readline()
    f.close()

year_i = first_line.split(",").index("APPT_START_DATE")

class MRVisitedBothYears(MRJob):
    
    def mapper(self, _, line):
        '''
        yields name as key, year as value
        '''
        info = line.split(",")
        year = re.search(r"2009|2010", info[year_i]) # only pulls 2009 or 2010
        name = ", ".join(info[:2]).strip(", ")
        if year and name:
            yield name, year.group(0)

    """ def reducer(self, name, year):
        years = set(year)
        if len(years) > 1:
            yield None, name """
    
    def reducer(self, name, year): 
        '''
        iterates through generator for each name, adds years to a set
        and as soon as it is clear the set contains both 2009 and 2010, 
        breaks loop and yields name 
        '''
        years = set()
        for x in year: 
            years.add(x)
            if len(years) > 1: 
                yield None, name
                break  # does this break function even for generators? 

if __name__ == '__main__': MRVisitedBothYears.run()
